#include "stm8s.h"
#include "rad.h"
#include "global.h"
#include "stm8s_it.h"

int baudrate;
bool data_complete,exit_command_mode;

void clk_init(void);
void Delay (uint16_t nCount);
void write_data_to _eeprom(bool);
void Read_data_from_eeprom (void);
void gpio_init(void);
void spi_init(void);

#define default 0
#define change  1
#define command_mode switch_position

int main (void)
{
  clk_init();
  gpio_init();
  write_data_to _eeprom(default);
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
        if(data_complete)
        {
            write_data_to _eeprom(change);
            read_data_from_eeprom();
            data_complete = 0;
        }
        else if(exit_command_mode)
        {
            break;
        }
    }
    if(data_received_RF)
    {
        data_received_RF = 0;
        send_data_uart(uart_send_buff);      
    }
    else if(data_received_UART)
    {
        data_received_UART = 0
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
  GPIO_Init(GPIOD,GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);
  GPIO_Init(GPIOC,GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);
  GPIO_Init(GPIOA,GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
  GPIO_Init(GPIOF,GPIO_Pin_0, GPIO_Mode_In_PU_IT);
  GPIO_Init(GPIOC,GPIO_Pin_1, GPIO_Mode_In_PU_IT);//  GPIO_Init(GPIOB,GPIO_Pin_1, GPIO_Mode_In_PU_IT);
  GPIO_Init(GPIOB,GPIO_Pin_2, GPIO_Mode_In_PU_IT);
  GPIO_Init(GPIOB,GPIO_Pin_3, GPIO_Mode_In_PU_IT);
  GPIO_Init(GPIOB,GPIO_Pin_4, GPIO_Mode_In_PU_IT);
  
  EXTI_SetPinSensitivity(EXTI_Pin_0, EXTI_Trigger_Falling); //gdo0
  EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling); //switch
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

//  /* Set MSD ChipSelect pin in Output push-pull high level */                                         // not required.
//  GPIO_Init(GPIOC, GPIO_PIN_4 , GPIO_MODE_OUT_PP_HIGH_SLOW);
  
  
  SPI_DeInit(SPI1);
  SPI_Init(SPI1,SPI_FirstBit_MSB, SPI_BaudRatePrescaler_2, SPI_Mode_Master, SPI_CPOL_Low,
           SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft,(uint8_t)0x07);
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, ENABLE);
  Delay(0xFFF);
  SPI_Cmd(SPI1,ENABLE);
}
