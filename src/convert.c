/** @file convert.c
 *  @brief Utility module for type conversions to avoid using external libraries
 *  @author Vladimir Zhelev
 *  @version 0.0.0
 *  @date November 3, 2026
 */

#include <stdint.h>

void int32_str(int32_t val, char* buffer)
{

    char temp[16];
    uint8_t i = 0;
    uint8_t j = 0;

    while (val > 0)
    {
        temp[i++] = (val % 10) + '0';
        val /= 10;
    }

    while (i > 0)
        buffer[j++] = temp[--i];

    buffer[j] = '\0';
}


