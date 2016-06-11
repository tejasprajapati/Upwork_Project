#include "eeprom.h"
#include "stdlib.h"
#include "at_command.h"
extern char baud_rate_array[8],did_array[5],cid_array[4],rid_array[4],mode_array[2],did_val;
extern unsigned long baudrate;
extern struct Comm_Parameters a;

void write_data_to_eeprom(void)
{
  /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

    /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
 
    if(a.change == 1)
    {   
      write_array_to_eeprom(baud_rate_addr,baud_rate_array);
      write_array_to_eeprom(did_addr,did_array);
      write_array_to_eeprom(ch_no_addr,cid_array);
      write_array_to_eeprom(mode_addr,mode_array);
//      write_array_to_eeprom(rid_addr,rid_array);  need to discuss.
      
      a.change = 0;
    }
    else if(a.change == 0)
    {
      write_array_to_eeprom(baud_rate_addr,"38400");
      write_array_to_eeprom(did_addr,"002");
      write_array_to_eeprom(ch_no_addr,"11");
      write_array_to_eeprom(mode_addr,"B");
//      write_array_to_eeprom(rid_addr,rid_array); need to discuss.
    }
}

void read_data_from_eeprom()
{
  read_array_from_eeprom(baud_rate_addr,baud_rate_array);
  baudrate = atol(baud_rate_array);
  read_array_from_eeprom(did_addr,did_array);
  did_val = atoi(did_array);
  read_array_from_eeprom(ch_no_addr,cid_array);
  read_array_from_eeprom(mode_addr,mode_array);
 // read_array_from_eeprom(rid_addr,rid_array);   need to discuss.
}

void write_array_to_eeprom(uint32_t addr,char * array)
{
      uint8_t i = 0;
      while(array[i] != '\0')
      {
        FLASH_EraseByte(addr);
        FLASH_ProgramByte((addr),array[i]);
        addr++;
        i++;
      }
      FLASH_ProgramByte((addr),array[i]);
}

void read_array_from_eeprom(uint32_t addr,char * array)
{
      uint8_t i = 0,temp = '\0';
      while(1)
      {
        temp = FLASH_ReadByte(addr);
        if(temp != '\0')
        {
          array[i] = temp;
          temp = '\0';
          i++;
          addr++;
        }
        else
        {
          break;
        }
      }
}