#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veeprom.h"

int main(int argc, char *argv[])
{
    uint16_t addr;
    uint8_t data;
    int ret;

    veeprom_init();

    if (argc < 2)
    {
        printf("Usage:\n");
        printf("  %s write <addr> <data>\n", argv[0]);
        printf("  %s read  <addr>\n", argv[0]);
        printf("  %s erase\n", argv[0]);
        return 0;
    }

    /* WRITE command */
    if (strcmp(argv[1], "write") == 0)
    {
        if (argc != 4)
        {
            printf("Invalid arguments for write\n");
            return 0;
        }

        addr = strtol(argv[2], NULL, 0);
        data = strtol(argv[3], NULL, 0);

        ret = veeprom_write(addr, data);

        if (ret == EEPROM_OK)
        {
            printf("WRITE OK : addr = 0x%02X data = 0x%02X\n", addr, data);
        }
        else if (ret == EEPROM_ERR_ADDR)
        {
            printf("WRITE FAILED : Invalid address (0x00 - 0x%02X)\n",
                   EEPROM_SIZE - 1);
        }
        else
        {
            printf("WRITE FAILED\n");
        }
    }

    /* READ command */
    else if (strcmp(argv[1], "read") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid arguments for read\n");
            return 0;
        }

        addr = strtol(argv[2], NULL, 0);

        ret = veeprom_read(addr, &data);

        if (ret == EEPROM_OK)
        {
            printf("READ OK : addr = 0x%02X data = 0x%02X\n", addr, data);
        }
        else
        {
            printf("READ FAILED : Invalid address (0x00 - 0x%02X)\n",
                   EEPROM_SIZE - 1);
        }
    }

    /* ERASE command */
    else if (strcmp(argv[1], "erase") == 0)
    {
        veeprom_erase();
        printf("EEPROM ERASED (size = %d bytes)\n", EEPROM_SIZE);
    }

    else
    {
        printf("UNKNOWN command\n");
    }

    return 0;
}
