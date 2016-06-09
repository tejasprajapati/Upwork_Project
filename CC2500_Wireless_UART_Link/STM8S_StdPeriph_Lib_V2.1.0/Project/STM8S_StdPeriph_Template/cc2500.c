#include "rad.h"
#include "stm8s_spi.h"
#include "string.h"
#include "at_command.h"


unsigned char response_aray[65];
extern char rid_array[4],did_val;
extern struct Comm_Parameters a;
char register_addr[50] = {REG_IOCFG2,\
                          REG_IOCFG1,\
                          REG_IOCFG0,\
                          REG_FIFOTHR,\
                          REG_SYNC1,\
                          REG_SYNC0,\
                          REG_PKTLEN,\
                          REG_PKTCTRL1,\
                          REG_PKTCTRL0,\
                          REG_ADDR,\
                          REG_CHANNR,\
                          REG_FSCTRL1,\
                          REG_FSCTRL0,\
                          REG_FREQ2,\
                          REG_FREQ1,\
                          REG_FREQ0,\
                          REG_MDMCFG4,\
                          REG_MDMCFG3,\
                          REG_MDMCFG2,\
                          REG_MDMCFG1,\
                          REG_MDMCFG0,\
                          REG_DEVIATN,\
                          REG_MCSM2,\
                          REG_MCSM1,\
                          REG_MCSM0,\
                          REG_FOCCFG,\
                          REG_BSCFG,\
                          REG_AGCCTRL2,\
                          REG_AGCCTRL1,\
                          REG_AGCCTRL0,\
                          REG_WOREVT1,\
                          REG_WOREVT0,\
                          REG_WORCTRL,\
                          REG_FREND1,\
                          REG_FREND0,\
                          REG_FSCAL3,\
                          REG_FSCAL2,\
                          REG_FSCAL1,\
                          REG_FSCAL0,\
                          REG_RCCTRL1,\
                          REG_RCCTRL0,\
                          REG_FSTEST,\
                          REG_PTEST,\
                          REG_AGCTEST,\
                          REG_TEST2,\
                          REG_TEST1,\
                          REG_TEST0
};

char register_value[50] = {VAL_IOCFG2,\
                          VAL_IOCFG1,\
                          VAL_IOCFG0,\
                          VAL_FIFOTHR,\
                          VAL_SYNC1,\
                          VAL_SYNC0,\
                          VAL_PKTLEN,\
                          VAL_PKTCTRL1,\
                          VAL_PKTCTRL0,\
                          VAL_ADDR,\
                          VAL_CHANNR,\
                          VAL_FSCTRL1,\
                          VAL_FSCTRL0,\
                          VAL_FREQ2,\
                          VAL_FREQ1,\
                          VAL_FREQ0,\
                          VAL_MDMCFG4,\
                          VAL_MDMCFG3,\
                          VAL_MDMCFG2,\
                          VAL_MDMCFG1,\
                          VAL_MDMCFG0,\
                          VAL_DEVIATN,\
                          VAL_MCSM2,\
                          VAL_MCSM1,\
                          VAL_MCSM0,\
                          VAL_FOCCFG,\
                          VAL_BSCFG,\
                          VAL_AGCCTRL2,\
                          VAL_AGCCTRL1,\
                          VAL_AGCCTRL0,\
                          VAL_WOREVT1,\
                          VAL_WOREVT0,\
                          VAL_WORCTRL,\
                          VAL_FREND1,\
                          VAL_FREND0,\
                          VAL_FSCAL3,\
                          VAL_FSCAL2,\
                          VAL_FSCAL1,\
                          VAL_FSCAL0,\
                          VAL_RCCTRL1,\
                          VAL_RCCTRL0,\
                          VAL_FSTEST,\
                          VAL_PTEST,\
                          VAL_AGCTEST,\
                          VAL_TEST2,\
                          VAL_TEST1,\
                          VAL_TEST0
};

void delay_ms(__IO uint32_t nTime) 
{
  __IO uint32_t TimingDelay = 0;
  TimingDelay = nTime;
  for(TimingDelay=0; TimingDelay<nTime; TimingDelay++);
}
char Read(char add)
{
	unsigned char y;
	add = add + 0x80; //MSB OF ADR IS HIGH FOR READ

	ss_low;    //lo

        while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
        SPI_SendData(add);
	/*SPI_SendData(SPI1, add);                                              SEND ADR BYTE*/
        while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	y = SPI_ReceiveData();

        while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	SPI_SendData(0); //SEND PROXY DATA
        while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	y = SPI_ReceiveData(); //getcSPI1();

	ss_high;	// hi
	return y;
}

void WriteReg(char add, char data) 
{
	unsigned char y;
	ss_low;    //lo

        while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	SPI_SendData(add); // putcSPI1(add);         			//SEND ADR BYTE
        while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	y = SPI_ReceiveData();

        while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	SPI_SendData(data); //SEND PROXY DATA
        while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	y = SPI_ReceiveData(); //getcSPI1();

	ss_high;	// hi
}
  
char SendStrobe(char strobe) 
{
	unsigned char out;
	ss_low;    //lo

        while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	SPI_SendData(strobe); //SEND STROBE BYTE
        while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	out = SPI_ReceiveData(); 

	ss_high;	// hi
	return out;
}
void cc2500_mode(char mode)
{
        delay_ms(50000);
	if(mode==1)
	{
                SendStrobe(CC2500_IDLE);
                SendStrobe(CC2500_FRX);
		SendStrobe(CC2500_RX);				//	RX: enable RX
	}
	else if(mode == 0)
	{
	//	SendStrobe(CC2500_TX);				// TX mode enable (need to think about logic)
		SendStrobe(CC2500_IDLE);
	}
}
void send_data_rf(char *data) 
{               //{length|dst_addr|send_addr|data|crc}   // from code only send address(3 btyes) + data.
    char data_to_send[50], i, length = strlen(data),rid_val;
 //   char length = strlen(data_to_send);
    memset(data_to_send,0x00,sizeof(data_to_send));
    
    if(a.data_received_from_UART)
    {
      strncpy(rid_array,data,3);
      rid_val = atoi(rid_array);
      data_to_send[0] = length - 1 ;                                              // reducing the address bytes from the message length. 
      data_to_send[1] = rid_val;
      data_to_send[2] = did_val;
      strcat(data_to_send,(data+3));
    }
    else
    {
      data_to_send[0] = length;                 // only for acknowledge                                  
      strcat(data_to_send,(data));
    }

    SendStrobe(CC2500_IDLE);                                                    /*Make sure that the radio is in IDLE state before flushing the FIFO*/
    delay_ms(5);
    SendStrobe(CC2500_FTX);                                                     /*Flush TX FIFO*/
    delay_ms(5);
    SendStrobe(CC2500_IDLE);	                                                /*SIDLE: exit RX/TX*/
    delay_ms(5);

    for (i = 0; i < length; i++) 
    {
      WriteReg(CC2500_TXFIFO, data_to_send[i]);
    }
    
    GPIO_Init(GPIOC,GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);                              /*GDO0 IT disable*/
    SendStrobe(CC2500_TX);                                                      /*STX: enable TX*/
    while(!(GPIOC->IDR & GPIO_PIN_3));                                          /*Wait for GDO0 to be set -> sync transmitted*/

    while(GPIOC->IDR & GPIO_PIN_3);                                             /*Wait for GDO0 to be cleared -> end of packet*/	
    GPIO_Init(GPIOC,GPIO_PIN_3, GPIO_MODE_IN_PU_IT);                              /*GDO0 IT enable*/
//    delay_ms(5000);
}

void init_CC2500(void)
{
  char i;
  for(i = 0; i < strlen(register_addr); i++)
    WriteReg(register_addr[i], register_value[i]);
//	WriteReg(REG_IOCFG2, VAL_IOCFG2);
//	WriteReg(REG_IOCFG1, VAL_IOCFG1);
//	WriteReg(REG_IOCFG0, VAL_IOCFG0);
////        WriteReg(REG_POWER,VAL_POWER);
//	WriteReg(REG_FIFOTHR, VAL_FIFOTHR);
//	WriteReg(REG_SYNC1, VAL_SYNC1);
//	WriteReg(REG_SYNC0, VAL_SYNC0);
//	WriteReg(REG_PKTLEN, VAL_PKTLEN);
//	WriteReg(REG_PKTCTRL1, VAL_PKTCTRL1);
//	WriteReg(REG_PKTCTRL0, VAL_PKTCTRL0);
//	WriteReg(REG_ADDR, VAL_ADDR);    //VAL_ADDR    did_val         // did added by ronak for address check.
//	WriteReg(REG_CHANNR, VAL_CHANNR);
//	WriteReg(REG_FSCTRL1, VAL_FSCTRL1);
//	WriteReg(REG_FSCTRL0, VAL_FSCTRL0);
//	WriteReg(REG_FREQ2, VAL_FREQ2);
//	WriteReg(REG_FREQ1, VAL_FREQ1);
//	WriteReg(REG_FREQ0, VAL_FREQ0);
//	WriteReg(REG_MDMCFG4, VAL_MDMCFG4);
//	WriteReg(REG_MDMCFG3, VAL_MDMCFG3);
//	WriteReg(REG_MDMCFG2, VAL_MDMCFG2);
//	WriteReg(REG_MDMCFG1, VAL_MDMCFG1);
//	WriteReg(REG_MDMCFG0, VAL_MDMCFG0);
//	WriteReg(REG_DEVIATN, VAL_DEVIATN);
//	WriteReg(REG_MCSM2, VAL_MCSM2);
//	WriteReg(REG_MCSM1, VAL_MCSM1);
//	WriteReg(REG_MCSM0, VAL_MCSM0);
//	WriteReg(REG_FOCCFG, VAL_FOCCFG);
//
//	WriteReg(REG_BSCFG, VAL_BSCFG);
//	WriteReg(REG_AGCCTRL2, VAL_AGCCTRL2);
//	WriteReg(REG_AGCCTRL1, VAL_AGCCTRL1);
//	WriteReg(REG_AGCCTRL0, VAL_AGCCTRL0);
//	WriteReg(REG_WOREVT1, VAL_WOREVT1);
//	WriteReg(REG_WOREVT0, VAL_WOREVT0);
//	WriteReg(REG_WORCTRL, VAL_WORCTRL);
//	WriteReg(REG_FREND1, VAL_FREND1);
//	WriteReg(REG_FREND0, VAL_FREND0);
//	WriteReg(REG_FSCAL3, VAL_FSCAL3);
//	WriteReg(REG_FSCAL2, VAL_FSCAL2);
//	WriteReg(REG_FSCAL1, VAL_FSCAL1);
//	WriteReg(REG_FSCAL0, VAL_FSCAL0);
//	WriteReg(REG_RCCTRL1, VAL_RCCTRL1);
//	WriteReg(REG_RCCTRL0, VAL_RCCTRL0);
//	WriteReg(REG_FSTEST, VAL_FSTEST);
//	WriteReg(REG_PTEST, VAL_PTEST);
//	WriteReg(REG_AGCTEST, VAL_AGCTEST);
//	WriteReg(REG_TEST2, VAL_TEST2);
//	WriteReg(REG_TEST1, VAL_TEST1);
//	WriteReg(REG_TEST0, VAL_TEST0);
	/*
	 WriteReg(REG_RTNUM,VAL_PARTNUM);
	 WriteReg(REG_VERSION,VAL_VERSION);
	 WriteReg(REG_FREQEST,VAL_FREQEST);
	 WriteReg(REG_LQI,VAL_LQI);
	 WriteReg(REG_RSSI,VAL_RSSI);
	 WriteReg(REG_MARCSTATE,VAL_MARCSTATE);
	 WriteReg(REG_WORTIME1,VAL_WORTIME1);
	 WriteReg(REG_WORTIME0,VAL_WORTIME0);
	 WriteReg(REG_PKTSTATUS,VAL_PKTSTATUS);
	 WriteReg(REG_VCO_VC_DAC,VAL_VCO_VC_DAC);
	 WriteReg(REG_TXBYTES,VAL_TXBYTES);
	 WriteReg(REG_RXBYTES,VAL_RXBYTES);
	 WriteReg(REG_RCCTRL1_STATUS,VAL_RCCTRL1_STATUS);
	 WriteReg(REG_RCCTRL0_STATUS,VAL_RCCTRL0_STATUS);
	 */
}
void Read_Config_Regs(void)
{
	unsigned int addr = 0,inc=0;
	for(inc=0;inc<99;inc++)
	{
            response_aray[inc]=Read(addr++);
	}
}
void setup(void) 
{
	ss_high;
//	SS=1;

	delay_ms(1000);
//        Read_Config_Regs();
	init_CC2500();
//        Read_Config_Regs();
//	delay_ms(1000);
        cc2500_mode(1);  //configure device in rx/tx mode (1 - rx ,0 - tx) 
}
