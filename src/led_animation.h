/**
 * @file led_animation.h
 * @author Wimanshahb@gmail.com
 * @brief
 * @version 0.1
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef LED_ANIMATION_H
#define LED_ANIMATION_H

#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BRIGHTNESS 255  // Maximum brightness for the LED
#define BREATHING_STEPS 100 // Number of steps in the breathing cycle
#define BREATHING_PERIOD 10 // Delay between updates (in milliseconds)

#define NUM_LEDS 26    // Total number of LEDs on the strip
#define SWEEP_SPEED 1  // Speed of the rainbow sweep (lower is faster)
#define SWEEP_DELAY 50 // Delay between updates (in milliseconds)

#define GLITCH_DURATION 50 // Duration for the glitch in milliseconds
#define GLITCH_DELAY 50    // Delay between glitch cycles in milliseconds
#define GLITCH_INTENSITY 6 // Number of LEDs to glitch at once

#define EXPLOSION_STEPS 15 // Number of expansion steps in the explosion

#define NUM_COLORS 3 // Number of colors in patterns

#define DELAY_TIME K_MSEC(2000)

enum HolidayMode
{
    HOLIDAY_CHRISTMAS,
    HOLIDAY_HALLOWEEN,
    HOLIDAY_FIREPLACE
};

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 16
#define J 15
#define K 14
#define L 13
#define M 12
#define N 11
#define O 10
#define P 9
#define Q 8
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

struct led_strip
{
    struct device *dev;
    size_t num_of_leds;
    struct led_rgb *led_rgb_array;
};

void display_pattern_mod(char *pattern, size_t len, struct led_strip led_strip_struct);
void display_pattern_all_off(struct led_strip led_strip_struct);
void random_glitch(size_t num_leds, struct led_strip led_Strip_struct);
void rainbow_sweep(size_t num_leds, struct led_strip led_strip_struct);
void comet_effect(struct led_strip strip, uint8_t r, uint8_t g, uint8_t b, size_t tail_length);
void firework_explosion(struct led_strip strip);
void fire_flicker(struct led_strip strip);

#endif