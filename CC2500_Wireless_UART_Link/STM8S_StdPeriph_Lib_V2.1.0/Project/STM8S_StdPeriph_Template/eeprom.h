#ifndef EEPROM_H

#define EEPROM_H

#include "stm8s.h"
#include "stm8s_flash.h"

extern char baud_rate_array[8],did_array[5],cid_array[4],rid_array[4],mode_array[2];

#define baud_rate_addr  0x4005
#define did_addr        0x400F
#define ch_no_addr      0x4015
#define mode_addr       0x401A

void write_array_to_eeprom(uint32_t, char *);
void read_array_from_eeprom(uint32_t,char *);
void write_data_to_eeprom(char );
void read_data_from_eeprom();

#endif