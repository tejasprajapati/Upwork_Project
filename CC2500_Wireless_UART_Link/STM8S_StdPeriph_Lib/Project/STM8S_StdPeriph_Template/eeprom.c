#include "eeprom.h"

extern uint8_t baud_rate_array[8],did_array[5],ch_no_array[4];

void write_data_to_eeprom(char change_data)
{
  /* Define FLASH programming time */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

    /* Unlock Data memory */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
 
    if(change_data == 1)
    {
      write_array_to_eeprom(baud_rate_addr,baud_rate_array);
      write_array_to_eeprom(did_addr,did_array);
      write_array_to_eeprom(ch_no_addr,ch_no_array);
    } 
    else if(change_data == 0)
    {
      write_array_to_eeprom(baud_rate_addr,"115200");
      write_array_to_eeprom(did_addr,"255");
      write_array_to_eeprom(ch_no_addr,"11");
    }
}

void read_data_from_eeprom()
{
  read_array_from_eeprom(baud_rate_addr,baud_rate_array);
  read_array_from_eeprom(did_addr,did_array);
  read_array_from_eeprom(ch_no_addr,ch_no_array);
}

void write_array_to_eeprom(uint32_t addr,uint8_t* array)
{
      uint8_t i = 0;
      while(array[i] != '\0')
      {
        FLASH_EraseByte(addr);
        FLASH_ProgramByte((addr),array[i]);
        addr++;
        i++;
      }
}

void read_array_from_eeprom(uint32_t addr,uint8_t* array)
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