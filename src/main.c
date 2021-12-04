/**
 * @file main.c
 * @brief  Original code from: https://github.com/abhra0897/stm8_fun
 * 
 * Simulate the flame of a candle with WS2812B LEDs.
 * 
 */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include "stm8s.h"
#include "spi.h"
#include "ws2812_driver.h"
#include "random8.h"
#include "color_palette.h"
#include "utils.h"
#include "color_utils.h"

#define LED_COUNT 5
#define COLOR_UPPER_BOUND 110
#define COLOR_LOWER_BOUND 94

uint16_t rand16seed = 1337;

CRGB leds_color[LED_COUNT];


void main(void)
{
    /* Set clock to full speed (16 Mhz) */
    CLK_CKDIVR = 0;


    ws2812_gpio_config();

    uint8_t color_buff[LED_COUNT][3];

    uint8_t color_indexes[LED_COUNT];
    memset(color_indexes, (COLOR_UPPER_BOUND+COLOR_LOWER_BOUND)/2, sizeof(color_indexes));
    uint8_t brightness[LED_COUNT];
    memset(brightness, 200, sizeof(brightness));

    while (1)
    {
        for (uint8_t led_cnt = 0; led_cnt < LED_COUNT; led_cnt++)
        {
            uint8_t offset = random8_upper_lim(3);
            uint8_t sign = random8_upper_lower_lim(0, 2);
            if (sign == 0)
            {
                color_indexes[led_cnt] = bound8(color_indexes[led_cnt] - offset, COLOR_LOWER_BOUND, COLOR_UPPER_BOUND);
            }
            else
            {
                color_indexes[led_cnt] = bound8(color_indexes[led_cnt] + offset, COLOR_LOWER_BOUND, COLOR_UPPER_BOUND);
            }

            offset = random8_upper_lim(3);
            sign = random8_upper_lower_lim(0, 2);
            if (sign == 0)
            {
                brightness[led_cnt] = bound8(brightness[led_cnt] - offset, 190, 220);
            }
            else
            {
                brightness[led_cnt] = bound8(brightness[led_cnt] + offset, 190, 220);
            }

            CRGB colors;
            ColorFromPalette(HeatColors_p, color_indexes[led_cnt], brightness[led_cnt], 1, &colors);

            color_buff[led_cnt][0] = colors.r;
            color_buff[led_cnt][1] = colors.g;
            color_buff[led_cnt][2] = colors.b;
        }

        for (uint8_t led_cnt = 0; led_cnt < LED_COUNT; led_cnt++)
        {
            ws2812_send_pixel_24bits(color_buff[led_cnt][0], color_buff[led_cnt][1], color_buff[led_cnt][2]);
        }
        ws2812_send_latch();

        for (uint32_t jj = 0; jj < 50000; jj++)
            ;
    }

    while (1)
        ;
}