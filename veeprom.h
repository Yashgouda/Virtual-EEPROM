#ifndef VEEPROM_H
#define VEEPROM_H

#include <stdint.h>

#define EEPROM_SIZE   64
#define EEPROM_FILE   "eeprom.bin"

#define EEPROM_OK            0
#define EEPROM_ERR_ADDR     -1
#define EEPROM_ERR_FILE     -2

void veeprom_init(void);
int veeprom_write(uint16_t addr, uint8_t data);
int veeprom_read(uint16_t addr, uint8_t *data);
void veeprom_erase(void);

#endif