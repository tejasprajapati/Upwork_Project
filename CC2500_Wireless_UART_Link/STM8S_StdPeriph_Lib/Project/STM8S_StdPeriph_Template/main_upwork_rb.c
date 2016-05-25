#include "stm8s.h"
#include "rad.h"
#include "global.h"
#include "stm8s_it.h"
#include "at_command.h"
#include "uart.h"
#include "eeprom.h"

int baudrate, command_mode;
uint8_t baud_rate_array[8],did_array[5],ch_no_array[4];
bool data_complete,exit_command_mode;
char RF_send_buff[MAX_BUF_SIZE];
char Uart_send_buff[MAX_BUF_SIZE];
struct Comm_Parameters a;
//enum Opeartion_Mode Op_mode;

void clk_init(void);
void Delay (uint16_t nCount);
void write_data_to_eeprom(bool);
void Read_data_from_eeprom (void);
void gpio_init(void);
void spi_init(void);

#define default 0
#define change  1
//#define command_mode switch_position


int main (void)
{
  clk_init();
  gpio_init();
  write_data_to_eeprom(default);
  read_data_from_eeprom();
  uart_init(baudrate);
  spi_init();
  setup();              // configure the cc2500 in required format.
                        /* Enable general interrupts */
  enableInterrupts();
  
  while (1)
  {
    while(command_mode)
    {
      if(a.data_complete)
      {
        write_data_to_eeprom(change);
        read_data_from_eeprom();
        a.data_complete = 0;
      }
      else if(a.exit_command_mode)
      {
        break;
      }
    }
    if(a.data_received_from_RF)
    {
        a.data_received_from_RF = 0;
        send_data_uart(Uart_send_buff);      
    }
    else if(a.data_received_from_UART)
    {
        a.data_received_from_UART = 0;
        send_data_rf(RF_send_buff);
    }
  }
}

/**
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
void Delay(uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

void clk_init(void)
{
    /*High speed internal clock prescaler: 1*/
   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

void gpio_init(void)
{
  GPIO_Init(GPIOC,GPIO_PIN_3, GPIO_MODE_IN_PU_IT);                              /*GDO0*/
  GPIO_Init(GPIOD,GPIO_PIN_3, GPIO_MODE_IN_PU_IT);                              /*Mode_switch*/
  
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
  
  Delay(0xFFF);
                                                                                                        /* SD_SPI enable */
  SPI_Cmd( ENABLE);
  
  GPIO_Init(GPIOC,GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);                      /*CS*/
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