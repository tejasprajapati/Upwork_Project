#ifndef AT_COMMAND_H

#define AT_COMMAND_H

#include <string.h>

#define MAX_BUF_SIZE    30

extern char RF_send_buff[MAX_BUF_SIZE], Uart_send_buff[MAX_BUF_SIZE];
extern unsigned int command_mode;

struct Comm_Parameters                                                          /*Structure for CC2500 and UART parameters*/
{
  unsigned data_complete : 1;
  unsigned exit_command_mode : 1;
  unsigned data_received_from_RF : 1;
  unsigned data_received_from_UART : 1;
  unsigned ack_received : 1;
  unsigned command_mode : 1;
  unsigned change : 1;
};

int check_crc(char const *, int);                                               /*Function to check the CRC*/

#endif