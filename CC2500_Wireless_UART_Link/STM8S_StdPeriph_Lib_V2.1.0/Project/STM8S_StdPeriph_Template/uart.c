#include "stm8s.h"
#include "uart.h"

unsigned char index = 0;

void uart_init(long baudrate)
{
  switch(baudrate)
  {
  case 4800:
  case 9600:
  case 19200:
  case 38400:
  case 57600:
  case 115200:
    break;
  default:
    baudrate = 9600;
    break;
  }
  UART1_Init((uint32_t)baudrate, UART1_WORDLENGTH_8D,UART1_STOPBITS_1, UART1_PARITY_NO,
                   UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);

  /* Enable UART */
  UART1_Cmd(ENABLE);
}

void send_data_uart(char *uart_send_buff)
{
  index = 0;
  strcat(uart_send_buff,"\n");
  while(uart_send_buff[index] != '\0')
  {
      UART1_SendData8(uart_send_buff[index]);
      /* Wait until end of transmit */
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
      index++;
  }
}