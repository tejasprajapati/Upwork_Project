char *Buadrates[6] =                                                            /*Return message which can be printed on console easily*/
{
  "4800",
  "9600",
  "19200",
  "38400",
  "57600",
  "115200",
};

char *Trans_mode[2] = 
{
  "Addressing mode",
  "Broadcasting mode"
};

char *Freq[]                                                                    /*Number of frequencies currently unknown*/
{
};

enum Transmission_Mode                                                          /*Enum for transmission mode to be selected*/
{
  ADDRESS_MODE,
  BROADCAST_MODE,
};

enum Frequency                                                                  /*Enum for transmission frequency to be set*/
{
  ADDRESS_MODE,
  BROADCAST_MODE,
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

struct Comm_Parameters                                                          /*Structure for CC2500 and UART parameters*/
{
  enum Transmission_Mode CC2500_Mode;
  enum Frequency CC2500_Frequency;
  enum Bauds UART_Baudrates;
}


char * set_addressing_mode(enum Transmission_Mode);                             /*Set addressing mode in CC2500*/
char * get_addressing_mode(void);                                               /*Get current addressing mode in CC2500*/
char * set_channel_frequency(enum Frequency);                                   /*Set channel frequency in CC2500*/
char * get_channel_frequency(void);                                             /*Get current channel frequency in CC2500*/
char * set_baudrate(enum Bauds);                                                /*Set Buadrate for UART communication*/
char * get_baudrate(void);                                                      /*Get Buadrate for UART communication*/
