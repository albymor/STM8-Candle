/**
 * @file utils.c
 * @brief Code taken from: https://github.com/FastLED/FastLED
 */

#include "utils.h"

/**
 * @brief Divide by 16
 * 
 * @param dividend 
 * @return uint8_t 
 */
inline uint8_t lsrX4(uint8_t dividend)
{
    dividend >>= 4;
    return dividend;
}

/**
 * @brief Scale a 8-bit to a given number. i * scale / 256
 * 
 * @param i 
 * @param scale 
 * @return uint8_t 
 */
uint8_t scale8(uint8_t i, uint8_t scale)
{
    return ((uint16_t)i * (uint16_t)(scale)) >> 8;
}

/**
 * @brief Bound an uint8_t to a range.
 * 
 * @param val 
 * @param min 
 * @param max 
 * @return uint8_t 
 */
uint8_t bound8(uint8_t val, uint8_t min, uint8_t max)
{
    if (val < min)
    {
        return min;
    }
    else if (val > max)
    {
        return max;
    }
    else
    {
        return val;
    }
}