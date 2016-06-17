#include "stm8s.h"
#include "rad.h"
#include "global.h"
#include "stm8s_it.h"
#include "at_command.h"
#include "uart.h"
#include "eeprom.h"
#include "stdlib.h"

#define default 0
#define true 1
#define false 0
#define led_on         GPIO_WriteHigh(GPIOD,GPIO_PIN_2);
#define led_off        GPIO_WriteLow(GPIOD,GPIO_PIN_2);


//unsigned int ack_received, command_mode, change;
unsigned long baudrate,wait_count;
char baud_rate_array[8],did_array[5],cid_array[4],rid_array[4],mode_array[2],did_val;
char RF_send_buff[MAX_BUF_SIZE];
char Uart_send_buff[MAX_BUF_SIZE];
char uart_rcv_buff[MAX_BUF_SIZE];
struct Comm_Parameters a;

void clk_init(void);
void Delay (uint16_t nCount);
void handle_uart_request(char *);
void check_for_parameter(char *, char); 
void write_data_to_eeprom(void);
void Read_data_from_eeprom (void);
void gpio_init(void);
void spi_init(void);



int main (void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);         //clk_init();
  gpio_init();
  write_data_to_eeprom();
//  read_data_from_eeprom();
  uart_init(baudrate);
  spi_init();
  setup();              // configure the cc2500 in required format.
                        /* Enable general interrupts */
  enableInterrupts();
  while (1)
  {
    
//    a.data_received_from_UART = 1;  // just for testing of cc2500
//    Delay(5000);
    while(a.command_mode)
    {
      led_on;
      if(a.data_complete)
      {
        handle_uart_request(uart_rcv_buff);
        write_data_to_eeprom();

        a.data_complete = 0;
      }
    }
    led_off;
    if(a.data_received_from_RF)
    {
        a.data_received_from_RF = 0;
        send_data_uart(Uart_send_buff+2);      
    }
    else if(a.data_received_from_UART)
    {
        int crc_got = 0;
        char length = strlen(RF_send_buff);
        a.ack_received = 0;
        crc_got = check_crc(RF_send_buff+3, length - 3);
        RF_send_buff[length] = ((crc_got & 0xFF00) >> 8);
        RF_send_buff[length + 1] = (crc_got & 0x00FF);
        send_data_rf(RF_send_buff);
        cc2500_mode(1);
        
        wait_count = 0;
        while((a.ack_received == 0) && wait_count++ <= 99999 );  // during testing received ack within 10000 count.//rb
        if(wait_count >= 99999)
        send_data_rf(RF_send_buff);
        cc2500_mode(1);
        
        a.data_received_from_UART = 0;
    }
  }
}

//void clk_init(void)
//{
//    /*High speed internal clock prescaler: 1*/
////   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
//}

void gpio_init(void)
{
  GPIO_Init(GPIOC,GPIO_PIN_3, GPIO_MODE_IN_PU_IT);                              /*GDO0 IT enable*/
  GPIO_Init(GPIOD,GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);                       /*Config_LED*/
  GPIO_Init(GPIOD,GPIO_PIN_3, GPIO_MODE_IN_PU_IT);                              /*Config_switch*/
  
  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);       /*GDO0 Interrupt*/
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);       /*Mode_switch Interrupt*/
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
}

void spi_init(void)
{
  SPI_DeInit();
                                                                                                          /* Set the MOSI,MISO and SCK at high level */
  GPIO_ExternalPullUpConfig(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5), ENABLE);
                                                                                                         /* SD_SPI Configuration */
  SPI_Init( SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,                                 // for baud rate we have to check else is done as per below working configuration.
           SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX,
           SPI_NSS_SOFT, 0x07);
  
  delay_ms(1000);
                                                                                                        /* SD_SPI enable */
  SPI_Cmd( ENABLE);
  
  GPIO_Init(GPIOC,GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);                      /*CS*/
}

inline char crc_ok(char * packet, int length)
{
  int rcvd_crc = packet[length - 2 ];
  rcvd_crc = rcvd_crc << 8;
  rcvd_crc |= packet[length - 1];
  int calc_crc = check_crc(packet + 2, length - 4);
  
  if(rcvd_crc == calc_crc)
    return true;
  else
    return false;
}
 
inline char address_check(char * packet)
{
  if((*(packet)== did_val)|(*(packet)== 0x00)|(*(packet)== 0xff))
    {
      return true;
    }
    else return false;
}
inline char no_broadcast(char * packet)
{
    if((*(packet)== 0x00)|(*(packet)== 0xff))
    {
      return false;
    }
    else return true;
}

inline char no_ack_msg(char *packet)
{
  char * ptr = NULL;
  ptr =  strstr(packet,"*ack*");
  if(ptr == NULL)
  {
    return true;
  }
  else
  {
    a.ack_received = 1;
    return false;
  }
}

inline void send_ack(char * packet)       //format {length|dst_addr|send_addr|data}
{
  char ack_msg[10];
  memset(ack_msg,0x00,sizeof(ack_msg));
  ack_msg[0] = *(packet + 1);          // address of sender need to get by other method this is wrong method.
  ack_msg[1] = did_val;
  strcat(ack_msg,"*ack*");
  strcat(ack_msg,"\r");
  send_data_rf(ack_msg);
  delay_ms(5000);
  cc2500_mode(1);
}

void handle_uart_request(char * uart_req)
{
  char *ptr = NULL, edit = 0;
  
//  check_for_parameter(uart_req);
  
  ptr = strstr(uart_req,"=");
  if(ptr != NULL)
  {
    edit = 1;
  }
  check_for_parameter(uart_req , edit);            
}


void check_for(char * parameter , char edit,char * value, char * array_to_save)
{
  unsigned char length;
  length = strlen(value);
  if(strncmp(parameter,value,length) == 0)                                       /*Baudrate*/
    { 
      if(edit)
      {
        strcpy(array_to_save,parameter + length + 1);
        a.change = 1;
      }
      else
      {
        send_data_uart(array_to_save);
      }
    }
}
void check_for_parameter(char * parameter , char edit)                          //BR,CID,DID,RID,MODE,RST
{
    check_for(parameter,edit,"AT+BR",baud_rate_array);                        //1st phase of optimization
    check_for(parameter,edit,"AT+CID",cid_array);
    check_for(parameter,edit,"AT+DID",did_array);
    check_for(parameter,edit,"AT+RID",rid_array);
    check_for(parameter,edit,"AT+MODE",mode_array);

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
