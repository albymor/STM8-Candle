/**
 * @file color_utils.h
 * @brief  Code taken from: https://github.com/FastLED/FastLED
 * 
 */
#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <stdint.h>

typedef struct
{
    union
    {
        struct
        {
            union
            {
                uint8_t f;
                uint8_t fake;
            };
            union
            {
                uint8_t r;
                uint8_t red;
            };
            union
            {
                uint8_t g;
                uint8_t green;
            };
            union
            {
                uint8_t b;
                uint8_t blue;
            };
        };
        uint8_t raw[4];
        uint32_t raw32;
    };
} CRGB;

void ColorFromPalette(const uint32_t *pal, uint8_t index, uint8_t brightness, uint8_t blendType, CRGB *colors);

#endif
