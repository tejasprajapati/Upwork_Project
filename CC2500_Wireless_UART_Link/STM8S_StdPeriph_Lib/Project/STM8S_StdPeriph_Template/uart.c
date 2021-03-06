#include "stm8s.h"
#include "uart.h"

unsigned char index = 0;

void uart_init(long baudrate)
{
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D,UART1_STOPBITS_1, UART1_PARITY_ODD,
                   UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  
  /* Enable the UART Transmit complete interrupt: this interrupt is generated 
     when the UART transmit Shift Register is empty */
//  UART1_ITConfig(UART1_IT_TXE, ENABLE);

  /* Enable UART */
  UART1_Cmd(ENABLE);
  
    /* Enable general interrupts */
//  enableInterrupts();
  
  
  
  
  
//  UART1_Cmd(DISABLE);
//  UART1_DeInit();
//  UART1_Init((uint32_t)baudrate, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, 
//              (UART1_SyncMode_TypeDef)(UART1_SYNCMODE_CLOCK_ENABLE | UART1_SYNCMODE_CPOL_LOW |UART1_SYNCMODE_CPHA_MIDDLE |UART1_SYNCMODE_LASTBIT_ENABLE),
//              UART1_MODE_TXRX_ENABLE);
//  
//  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
//    receive data register is not empty */
//  UART1_ITConfig(UART1_IT_RXNE, ENABLE);
//  UART1_ITConfig(UART1_IT_TXE | UART1_IT_TC, DISABLE);
//  
// /* Enable the UART1*/
//  UART1_Cmd(ENABLE);  
//  
//  enableInterrupts();
}

void send_data_uart(char *uart_send_buff)
{
  while(uart_send_buff[index] != '\0')
  {
      UART1_SendData8(uart_send_buff[index]);
      /* Wait until end of transmit */
      while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
      index++;
  }
}