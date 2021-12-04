/**
 * @file color_utils.c
 * @brief  Code taken from: https://github.com/FastLED/FastLED
 * 
 */

#include "color_utils.h"
#include "utils.h"

void ColorFromPalette(const uint32_t *pal, uint8_t index, uint8_t brightness, uint8_t blendType, CRGB *colors)
{
    //      hi4 = index >> 4;
    uint8_t hi4 = lsrX4(index);
    uint8_t lo4 = index & 0x0F;

    colors->raw32 = pal[hi4];

    uint8_t blend = lo4 && (blendType != 0);

    uint8_t red1 = colors->red;
    uint8_t green1 = colors->green;
    uint8_t blue1 = colors->blue;

    if (blend)
    {
        CRGB colors2;
        if (hi4 == 15)
        {
            colors2.raw32 = pal[0];
        }
        else
        {
            colors2.raw32 = pal[hi4 + 1];
        }

        uint8_t f2 = lo4 << 4;
        uint8_t f1 = 255 - f2;

        //    rgb1.nscale8(f1);
        uint8_t red2 = colors2.red;
        red1 = scale8(red1, f1);
        red2 = scale8(red2, f2);
        red1 += red2;

        uint8_t green2 = colors2.green;
        green1 = scale8(green1, f1);
        green2 = scale8(green2, f2);
        green1 += green2;

        uint8_t blue2 = colors2.blue;
        blue1 = scale8(blue1, f1);
        blue2 = scale8(blue2, f2);
        blue1 += blue2;
    }

    if (brightness != 255)
    {
        if (brightness)
        {
            ++brightness; // adjust for rounding
            // Now, since brightness is nonzero, we don't need the full scale8_video logic;
            // we can just to scale8 and then add one (unless scale8 fixed) to all nonzero inputs.
            if (red1)
            {
                red1 = scale8(red1, brightness);
            }
            if (green1)
            {
                green1 = scale8(green1, brightness);
            }
            if (blue1)
            {
                blue1 = scale8(blue1, brightness);
            }
        }
        else
        {
            red1 = 0;
            green1 = 0;
            blue1 = 0;
        }
    }

    colors->red = red1;
    colors->green = green1;
    colors->blue = blue1;
}
