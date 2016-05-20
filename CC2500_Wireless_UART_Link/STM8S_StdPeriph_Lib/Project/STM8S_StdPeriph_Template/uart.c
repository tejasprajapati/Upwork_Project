#include "stm8s.h"

unsigned char index = 0;

/* UART1 configuration -------------------------------------------------------*/
   /* UART1 configured as follow:
          - Word Length = 8 Bits
          - 1 Stop Bit
          - No parity
          - BaudRate = 9600 baud
          - UART1 Clock enabled
          - Polarity Low
          - Phase Middle
          - Last Bit enabled
          - Receive and transmit enabled
   */

void uart_init(baudrate)
{
  UART1_Cmd(DISABLE);
  
  UART1_DeInit();
  
  UART1_Init((uint32_t)baudrate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, 
              (UART1_SyncMode_TypeDef)(UART1_SYNCMODE_CLOCK_ENABLE | UART1_SYNCMODE_CPOL_LOW |UART1_SYNCMODE_CPHA_MIDDLE |UART1_SYNCMODE_LASTBIT_ENABLE),
              UART1_MODE_TXRX_ENABLE);
  
    /* Enable the UART1*/
  UART1_Cmd(ENABLE);  
}

void send_data_uart(uart_send_buff)
{
  while(uart_send_buff[index] != '\0')
  {
      UART1_SendData8(uart_send_buff[index]);
      /* Wait until end of transmit */
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
      {
      }
      index++;
  }
}