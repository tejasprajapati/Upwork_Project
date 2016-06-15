#ifndef EEPROM_H

#define EEPROM_H

#include "stm8s.h"
#include "stm8s_flash.h"

extern char baud_rate_array[8],did_array[5],cid_array[4],rid_array[4],mode_array[2];

#define baud_rate_addr  0x4000
#define did_addr        0x4010
#define ch_no_addr      0x4020
#define mode_addr       0x4030

void write_array_to_eeprom(uint32_t, char *);
void read_array_from_eeprom(uint32_t,char *);
void write_data_to_eeprom(void);
void read_data_from_eeprom(void);

#endif