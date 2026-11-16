/** @file format.c
 *  @brief Formatting functions for sensor measurements.
 *
 * Contains implementations of functions for producing display-ready
 * strings from raw sensor readings.
 *
 * @author Vladimir Zhelev
 */

#include <stdlib.h>
#include <stdint.h>

void format_humidity(uint32_t val, char* buffer)
{
    uint32_t exponent = (val / 1024);
    uint32_t mantissa = ((val % 1024) * 100) / 1024;

    size_t i = 0;
    size_t j = 0;
    char temp[16];

    while (i < 2)
    {
        temp[i++] = (mantissa % 10) + '0';
        mantissa /= 10;
    }

    temp[i++] = '.';

    do {
        temp[i++] = (exponent % 10) + '0';
        exponent /= 10;
    } while (exponent > 0);

    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j++] = '%';
    buffer[j++] = 'R';
    buffer[j++] = 'H';
    buffer[j] = '\0';
}

void format_pressure(uint32_t val, char* buffer)
{
    uint32_t exponent = (val / 25600);
    uint32_t mantissa = (val % 25600) / 256;

    size_t i = 0;
    size_t j = 0;
    char temp[16];

    while (i < 2)
    {
        temp[i++] = (mantissa % 10) + '0';
        mantissa /= 10;
    }

    temp[i++] = '.';

    do {
        temp[i++] = (exponent % 10) + '0';
        exponent /= 10;
    } while (exponent > 0);

    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j++] = 'h';
    buffer[j++] = 'P';
    buffer[j++] = 'a';
    buffer[j] = '\0';
}

void format_temp(int32_t val, char* buffer)
{
    uint32_t magnitude = (val < 0)
                       ? (uint32_t)(-(int64_t)val)
                       : (uint32_t)val;
    size_t i = 0;
    size_t j = 0;
    char temp[16];

    while (i < 2)
    {
        temp[i++] = (magnitude % 10) + '0';
        magnitude /= 10;
    }

    temp[i++] = '.';

    do {
        temp[i++] = (magnitude % 10) + '0';
        magnitude /= 10;
    } while (magnitude > 0);

    /* Attach sign */
    temp[i++] = (val < 0)
              ? '-'
              : '+';

    /* Fill buffer in reverse with assorted string */
    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j++] = 'C';
    buffer[j] = '\0';
}

void format_moisture(uint16_t val, char* buffer)
{
    uint32_t exponent = val / 100;
    uint32_t mantissa = val % 100;

    size_t i = 0;
    size_t j = 0;
    char temp[16];

    while (i < 2)
    {
        temp[i++] = (mantissa % 10) + '0';
        mantissa /= 10;
    }

    temp[i++] = '.';

    do {
        temp[i++] = (exponent % 10) + '0';
        exponent /= 10;
    } while (exponent > 0);

    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j++] = '%';
    buffer[j] = '\0';
}
