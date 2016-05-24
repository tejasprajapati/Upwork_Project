#include "at_command.h"
#include "rad.h"

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
//char * get_addressing_mode(void);                                               /*Get current addressing mode in CC2500*/
//char * set_channel_frequency(enum Frequency);                                   /*Set channel frequency in CC2500*/
//char * get_channel_frequency(void);                                             /*Get current channel frequency in CC2500*/
//char * set_remote_id(enum Frequency);                                           /*Set Remote ID for communication*/
//char * get_remote_id(void);                                                     /*Get Remote ID for communication*/
//char * set_baudrate(enum Bauds);                                                /*Set Buadrate for UART communication*/
//char * get_baudrate(void);                                                      /*Get Buadrate for UART communication*/
//char * reset_parameters(void);                                                  /*Reset the parameters to defualt*/
