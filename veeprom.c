#include <stdio.h>
#include <string.h>
#include "veeprom.h"

static FILE *fp;

/* Initialize EEPROM file */
void veeprom_init(void)
{
    fp = fopen(EEPROM_FILE, "rb+");
    if (!fp) 
    {
        // Create EEPROM file and initialize to 0xFF
        fp = fopen(EEPROM_FILE, "wb+");
        uint8_t ff = 0xFF;
        for (int i = 0; i < EEPROM_SIZE; i++)
            fwrite(&ff, 1, 1, fp);
    }
}

/* Write byte */
int veeprom_write(uint16_t addr, uint8_t data)
{
    if (addr >= EEPROM_SIZE)
        return EEPROM_ERR_ADDR;

    fseek(fp, addr, SEEK_SET);
    fwrite(&data, 1, 1, fp);
    fflush(fp);
    return EEPROM_OK;
}

/* Read byte */
int veeprom_read(uint16_t addr, uint8_t *data)
{
    if (addr >= EEPROM_SIZE)
        return EEPROM_ERR_ADDR;

    fseek(fp, addr, SEEK_SET);
    fread(data, 1, 1, fp);
    return EEPROM_OK;
}

/* Erase EEPROM */
void veeprom_erase(void)
{
    uint8_t ff = 0xFF;
    fseek(fp, 0, SEEK_SET);
    int i;
    for (i = 0; i < EEPROM_SIZE; i++)
        fwrite(&ff, 1, 1, fp);
    fflush(fp);
}
