#ifndef EEPROM_H

#define EEPROM_H

#include "stm8s_flash.h"

#define baud_rate_addr  0x4000
#define did_addr 0x400A
#define ch_no_addr 0x401A

void write_array_to_eeprom(uint32_t, uint8_t*);
void read_array_from_eeprom(uint32_t, uint8_t*);
void write_data_to_eeprom(char );
void read_data_from_eeprom();

#endif