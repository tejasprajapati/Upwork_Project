#include <stdio.h>
#include "at_command.h"
#include "rad.h"
#include "uart.h"
#include "eeprom.h"

static int set_baud;
char return_str[30];


char *set_addressing_mode(enum Transmission_Mode mode)
{
  WriteReg(REG_ADDR, mode);
  return "Register written with the setting.";
}

char get_addressing_mode(void)
{
  return ReadReg(REG_ADDR);
}

char * set_channel_frequency(enum Frequency freq)
{
  WriteReg(REG_CHANNR, freq);
  return "Selected frequency written.";
}

char get_channel_frequency(void)
{
  return ReadReg(REG_CHANNR);
}

char *set_baudrate(long baudrate)                                                /*Set Buadrate for UART communication*/
{
  send_data_uart("Caution you are going to chnage baudrate.\r\n");
  send_data_uart("Please update your baudrate settings.\r\n");
  switch(baudrate)
  {
    case 4800:
      set_baud = 1;
      break;
    case 19200:
      set_baud = 3;
      break;
    case 38400:
      set_baud = 4;
      break;
    case 57600:
      set_baud = 5;
      break;
    case 115200:
      set_baud = 6;
      break;
    case 9600:
    default:
      set_baud = 2;
      break;  
  }
  uart_init(baudrate);
  delay_ms(1000);
  memset(return_str, 0x00, sizeof(return_str));
  strcpy(return_str,"Baudrate changed.\r\n");
  
  return return_str;                                                            /*Print this string after some time so that User can see the 
                                                                                  Message.*/
}

char *get_baudrate(void)                                                        /*Get Buadrate for UART communication*/
{
  memset(return_str, 0x00, sizeof(return_str));
  
  switch(set_baud)
  {
    case 1:
      strcpy(return_str,"Buadrate is 4800\r\n");
      break;
    case 2:
      strcpy(return_str,"Buadrate is 9600.\r\n");
      break;
    case 3:
      strcpy(return_str,"Buadrate is 19200.\r\n");
      break;
    case 4:
      strcpy(return_str,"Buadrate is 38400.\r\n");
      break;
    case 5:
      strcpy(return_str,"Buadrate is 57600.\r\n");
      break;
    case 6:
      strcpy(return_str,"Buadrate is 115200.\r\n");
      break;
    default:
      strcpy(return_str,"Failed to get the baudrate.\r\n");
      break;  
  }
  return return_str;
}

char * reset_parameters(void)                                                   /*Reset the parameters to defualt*/
{
  long tmp_baudrate;
  read_data_from_eeprom();
  sscanf(baud_rate_array, "%ld", &tmp_baudrate);
  uart_init(tmp_baudrate);
//  sscanf(did_array, "%d", dev_id);
//  sscanf(cid_array, "%d", channel_id);
  memset(return_str, 0x00, sizeof(return_str));
 
  strcpy(return_str, "Parameters Reset.\r\n");
  
  return return_str;
}

//char * set_remote_id(enum Frequency);                                           /*Set Remote ID for communication*/
//char * get_remote_id(void);                                                     /*Get Remote ID for communication*/
//char * set_baudrate(enum Bauds);                                                /*Set Buadrate for UART communication*/
//char * get_baudrate(void);                                                      /*Get Buadrate for UART communication*/
//char * reset_parameters(void);                                                  /*Reset the parameters to defualt*/
