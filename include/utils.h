#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

inline uint8_t lsrX4(uint8_t dividend);
uint8_t scale8(uint8_t i, uint8_t scale);
uint8_t bound8(uint8_t val, uint8_t min, uint8_t max);

#endif
