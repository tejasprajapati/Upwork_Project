#ifndef RAD_H

#define RAD_H

#include "stm8s_gpio.h"
#include "stm8s.h"
#include "stdlib.h"

#define SS GPIO_Pin_4;
#define GDO GPIO_Pin_2;
#define MISO GPIO_Pin_6;
#define MOSI GPIO_Pin_7;
#define ss_low  GPIO_WriteLow(GPIOC, GPIO_PIN_4);                               /*GPIO_WriteBit(GPIOD,GPIO_Pin_3,RESET)*/
#define ss_high GPIO_WriteHigh(GPIOC, GPIO_PIN_4);                              /*GPIO_WriteBit(GPIOD,GPIO_Pin_3,SET)*/
//#define led(a) GPIOC->ODR = (a<<7);


void WriteReg(char add,char data);
char ReadReg(char add);
char Read(char add);
char SendStrobe(char strobe);
void init_CC2500(void);
void Read_Config_Regs(void);
void setup(void);
void delay_ms(__IO uint32_t nTime);
void loop_T(void);
void loop_R(void);
void TxData(unsigned char*);
char RxData(void);
void cc2500_mode(char);
void generate_id(int);
void send_data_rf(char *);
char no_broadcast(char *);
char crc_ok(char *, int);
char address_check(char *);
char no_ack_msg(char *);
void send_ack(char *);

/*****************************************************************/

#define CC2500_IDLE    0x36      // Exit RX / TX, turn
#define CC2500_TX      0x35      // Enable TX. If in RX state, only enable TX if CCA passes
#define CC2500_RX      0x34      // Enable RX. Perform calibration if enabled
#define CC2500_FTX     0x3B      // Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states
#define CC2500_FRX     0x3A      // Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states
#define CC2500_TXFIFO  0x3F		 // TX FIFO BUFFER
#define CC2500_RXFIFO  0x3F      // RX FIFO BUFFER


/***************************************************************/

//#define REG_IOCFG2           0x00
//#define REG_IOCFG1           0x01
#define REG_IOCFG0           0x02
#define REG_POWER            0x3E
//#define REG_FIFOTHR          0x03
//#define REG_SYNC1            0x04
//#define REG_SYNC0            0x05
#define REG_PKTLEN           0x32
#define REG_PKTCTRL1         0x07
#define REG_PKTCTRL0         0x08
//#define REG_ADDR             0x09
#define REG_CHANNR           0x0A
#define REG_FSCTRL1          0x0B
#define REG_FSCTRL0          0x0C
#define REG_FREQ2            0x0D
#define REG_FREQ1            0x0E
#define REG_FREQ0            0x0F
#define REG_MDMCFG4          0x10
#define REG_MDMCFG3          0x11
#define REG_MDMCFG2          0x12
//#define REG_MDMCFG1          0x13
//#define REG_MDMCFG0          0x14
#define REG_DEVIATN          0x15
//#define REG_MCSM2            0x16
#define REG_MCSM1            0x17
#define REG_MCSM0            0x18
#define REG_FOCCFG           0x19
//#define REG_BSCFG            0x1A
//#define REG_AGCCTRL2         0x1B
//#define REG_AGCCTRL1         0x1C
//#define REG_AGCCTRL0         0x1D
//#define REG_WOREVT1          0x1E
//#define REG_WOREVT0          0x1F
//#define REG_WORCTRL          0x20
//#define REG_FREND1           0x21
//#define REG_FREND0           0x22
//#define REG_FSCAL3           0x23
//#define REG_FSCAL2           0x24
#define REG_FSCAL1           0x25
#define REG_FSCAL0           0x26
//#define REG_RCCTRL1          0x27
//#define REG_RCCTRL0          0x28
//#define REG_FSTEST           0x29
//#define REG_PTEST            0x2A
//#define REG_AGCTEST          0x2B
//#define REG_TEST2            0x2C
//#define REG_TEST1            0x2D
//#define REG_TEST0            0x2E
/*
#define REG_PARTNUM          0x30
#define REG_VERSION          0x31
#define REG_FREQEST          0x32
#define REG_LQI              0x33
#define REG_RSSI             0x34
#define REG_MARCSTATE        0x35
#define REG_WORTIME1         0x36
#define REG_WORTIME0         0x37
#define REG_PKTSTATUS        0x38
#define REG_VCO_VC_DAC       0x39
#define REG_TXBYTES          0x3A
#define REG_RXBYTES          0x3B
#define REG_RCCTRL1_STATUS   0x3C
#define REG_RCCTRL0_STATUS   0x3D   
*/
/****************************************************************************

/* Sync word qualifier mode = 30/32 sync word bits detected */

/* Packet length mode = Fix packet length mode. Packet length configured by the first byte after sync word */

/* Whitening = false */

/* Data format = Normal mode */

/* Address config = No address check */

/* Channel spacing = 199.951172 *///if 26MHz then 8 gives 199.95k spacing (IF)

/* Carrier frequency = 2432.999908M*///5D93B1=6132657. Fc=(Fx/2^16)*FREQ;this value at 26MHz

/* Base frequency = 2432.999908M*/

/* RX filter BW = 203.125000k *///for 26MHz

/* Data rate = 2.39897k *///0x83=131d

/* Deviation = 38.085938k*/// at 26MHz

/* Device address = 0 *///AUTOMATICALY CALIBERATE WHEN GOING FROM IDLE TO TX/RX AND EXPIRY 64 COUNT

/* CRC autoflush = false */

/* Preamble count = 4 */

/* Manchester enable = false */

/* CRC enable = true */

/* Packet length = 6 */

/* Modulation format = 2-FSK */

/* Modulated = true */

/* Channel number = 0 */

/* {TX power = 0 }*/

/* PA table */

#define PA_TABLE {0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00}

/****************************************************************************



/**************************************************************************/
//#define VAL_IOCFG2           0x29//default chip ready
//#define VAL_IOCFG1           0x2E//default high impedence
#define VAL_IOCFG0           0x06// 0x06Asserts when word has sent/receive,de-asserts at end.In RX, pin will de-assert when address check fails or  RX FIFO overflows. In TX pin will de-assert if TX FIFO underflows.
#define VAL_POWER            0xfe// power value for RF operation.   
//#define VAL_FIFOTHR          0x07//33/32 in TX/RX
//#define VAL_SYNC1            0xD3//default 8 MSB
//#define VAL_SYNC0            0x91//default 8 LSB
#define VAL_PKTLEN           0x0C//6 length packet
#define VAL_PKTCTRL1         0x04//0x04 no addres check      // add address check and 0x00 broadcast (0x06)
#define VAL_PKTCTRL0         0x05// 0x04whitening off,CRC on, fix packet //variable packet length req.(0x05)
//#define VAL_ADDR             0x00//default no address      // address check required.(get did in it)
#define VAL_CHANNR           0x00//default channel no 0    // channel no. required to be add from the cid.
#define VAL_FSCTRL1          0x08//IF freq 199.95
#define VAL_FSCTRL0          0x00//default freq offset
#define VAL_FREQ2            0x5D//carrier freq 2432.M  5D93B1=6132657.
#define VAL_FREQ1            0x93//carrier freq 2432.M
#define VAL_FREQ0            0xB1//carrier freq 2432.M
#define VAL_MDMCFG4          0x86//BW 203k 0x8E
#define VAL_MDMCFG3          0x83//data rate 2.3989k change to 500.0 k baud rate 0x3B
#define VAL_MDMCFG2          0x03//30/32 detect 2-FSK
//#define VAL_MDMCFG1          0x22//default 4 preamble
//#define VAL_MDMCFG0          0xF8//default 199.95 spacing
#define VAL_DEVIATN          0x44//deviation 38.085k
//#define VAL_MCSM2            0x07//default time out untill packet end
#define VAL_MCSM1            0x30//0x2B//0x30//default If RSSI below threshold unless currently receiving packet  // ronak
#define VAL_MCSM0            0x18//64 expire , IDLE to TX/RX
#define VAL_FOCCFG           0x16//gate disable
//#define VAL_BSCFG            0x6c//default
//#define VAL_AGCCTRL2         0x03//default 33 db
//#define VAL_AGCCTRL1         0x40//default relative carrier sense disable
//#define VAL_AGCCTRL0         0x91//default normal operation, channel filter sample 16
//#define VAL_WOREVT1          0x87//default 876B=34667 appx. 1 s time out
//#define VAL_WOREVT0          0x6B//default 1 s time out
//#define VAL_WORCTRL          0xF8//default RC calibration on
//#define VAL_FREND1           0x56//default
//#define VAL_FREND0           0x10//default
//#define VAL_FSCAL3           0xA9//default
//#define VAL_FSCAL2           0x0A//default
#define VAL_FSCAL1           0x00//
#define VAL_FSCAL0           0x11//
//#define VAL_RCCTRL1          0x41//default
//#define VAL_RCCTRL0          0x00//default
//#define VAL_FSTEST           0x59//default
//#define VAL_PTEST            0x7F//default
//#define VAL_AGCTEST          0x3F//default
//#define VAL_TEST2            0x88//default
//#define VAL_TEST1            0x31//default
//#define VAL_TEST0            0x0B//default
/*********************************************************************/
/*
#define VAL_PARTNUM          0x80//default
#define VAL_VERSION          0x03//default
#define VAL_FREQEST          0x00//default
#define VAL_LQI              0x00//default
#define VAL_RSSI             0x00//default
#define VAL_MARCSTATE        0x00//default
#define VAL_WORTIME1         0x00//default
#define VAL_WORTIME0         0x00//default
#define VAL_PKTSTATUS        0x00//default
#define VAL_VCO_VC_DAC       0x00//default
#define VAL_TXBYTES          0x00//default
#define VAL_RXBYTES          0x00//default
#define VAL_RCCTRL1_STATUS   0x00//default
#define VAL_RCCTRL0_STATUS   0x00//default
*/

/*************************************************************************************/

#endif