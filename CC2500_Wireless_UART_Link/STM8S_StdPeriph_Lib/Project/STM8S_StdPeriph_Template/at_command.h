#ifndef AT_COMMAND_H

#define AT_COMMAND_H

//char *Buadrates[6] =                                                            /*Return message which can be printed on console easily*/
//{
//  "4800",
//  "9600",
//  "19200",
//  "38400",
//  "57600",
//  "115200",
//};

//char *Trans_mode[2] = 
//{
//  "Addressing mode",
//  "Broadcasting mode"
//};

/*char *Freq[] */                                                                   /*Number of frequencies currently unknown*/
/*{
};*/

enum Transmission_Mode                                                          /*Enum for transmission mode to be selected*/
{
  ADDRESS_MODE,
  BROADCAST_MODE,
};

enum Frequency                                                                  /*Using defualt frequency setting 500 channels can be created only 50 are 
                                                                                  Enumerated here.*/
{
  FREQ0,
  FREQ1,
  FREQ2,
  FREQ3,
  FREQ4,
  FREQ5,
  FREQ6,
  FREQ7,
  FREQ8,
  FREQ9,
  FREQ10,
  FREQ11,
  FREQ12,
  FREQ13,
  FREQ14,
  FREQ15,
  FREQ16,
  FREQ17,
  FREQ18,
  FREQ19,
  FREQ20,
  FREQ21,
  FREQ22,
  FREQ23,
  FREQ24,
  FREQ25,
  FREQ26,
  FREQ27,
  FREQ28,
  FREQ29,
  FREQ30,
  FREQ31,
  FREQ32,
  FREQ33,
  FREQ34,
  FREQ35,
  FREQ36,
  FREQ37,
  FREQ38,
  FREQ39,
  FREQ40,
  FREQ41,
  FREQ42,
  FREQ43,
  FREQ44,
  FREQ45,
  FREQ46,
  FREQ47,
  FREQ48,
  FREQ49,
  FREQ50,
};

enum Bauds
{
  BAUD_4800=4800,
  BAUD_9600=9600,
  BAUD_19200=19200,
  BAUD_38400=38400,
  BAUD_57600=57600,
  BAUD_115200=115200,
};

enum Operation_Mode
{
  COMMAND_MODE,
  NORMAL_OPERATION_MODE,
};

struct Comm_Parameters                                                          /*Structure for CC2500 and UART parameters*/
{
  enum Transmission_Mode CC2500_Mode;
  //enum Frequency CC2500_Frequency;
  enum Bauds UART_Baudrates;
  unsigned data_complete : 1;
  unsigned exit_command_mode : 1;
  unsigned data_received_from_RF : 1;
  unsigned data_received_from_UART : 1;
};


char * set_addressing_mode(enum Transmission_Mode);                             /*Set addressing mode in CC2500*/
char get_addressing_mode(void);                                                 /*Get current addressing mode in CC2500*/
char * set_channel_frequency(enum Frequency);                                   /*Set channel frequency in CC2500*/
char get_channel_frequency(void);                                               /*Get current channel frequency in CC2500*/
char * set_remote_id(enum Frequency);                                           /*Set Remote ID for communication*/
char * get_remote_id(void);                                                     /*Get Remote ID for communication*/
char * set_baudrate(enum Bauds);                                                /*Set Buadrate for UART communication*/
char * get_baudrate(void);                                                      /*Get Buadrate for UART communication*/
char * reset_parameters(void);                                                  /*Reset the parameters to defualt*/


#endif