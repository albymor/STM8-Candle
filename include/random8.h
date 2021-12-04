/**
 * @file random8.h
 * @brief Random number generator. Code taken from: https://github.com/FastLED/FastLED
 * 
 */
#ifndef __INC_LIB8TION_RANDOM_H
#define __INC_LIB8TION_RANDOM_H
#include <stdint.h>
///@ingroup lib8tion

///@defgroup Random Fast random number generators
/// Fast 8- and 16- bit unsigned random numbers.
///  Significantly faster than Arduino random(), but
///  also somewhat less random.  You can add entropy.
///@{

// X(n+1) = (2053 * X(n)) + 13849)
#define FASTLED_RAND16_2053  ((uint16_t)(2053))
#define FASTLED_RAND16_13849 ((uint16_t)(13849))

#if defined(LIB8_ATTINY)
#define APPLY_FASTLED_RAND16_2053(x) (x << 11) + (x << 2) + x
#else
#define APPLY_FASTLED_RAND16_2053(x) (x * FASTLED_RAND16_2053)
#endif

#define LIB8STATIC static inline

/// random number seed
extern uint16_t rand16seed;// = RAND16_SEED;

/// Generate an 8-bit random number
LIB8STATIC uint8_t random8()
{
    rand16seed = APPLY_FASTLED_RAND16_2053(rand16seed) + FASTLED_RAND16_13849;
    // return the sum of the high and low bytes, for better
    //  mixing and non-sequential correlation
    return (uint8_t)(((uint8_t)(rand16seed & 0xFF)) +
                     ((uint8_t)(rand16seed >> 8)));
}

/// Generate an 8-bit random number between 0 and lim
/// @param lim the upper bound for the result
LIB8STATIC uint8_t random8_upper_lim(uint8_t lim)
{
    uint8_t r = random8();
    r = (r*lim) >> 8;
    return r;
}

/// Generate an 8-bit random number in the given range
/// @param min the lower bound for the random number
/// @param lim the upper bound for the random number
LIB8STATIC uint8_t random8_upper_lower_lim(uint8_t min, uint8_t lim)
{
    uint8_t delta = lim - min;
    uint8_t r = random8_upper_lim(delta) + min;
    return r;
}

#endif
