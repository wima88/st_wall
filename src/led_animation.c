/**
 * @file led_animation.c
 * @author Wimanshahb@gmail.com
 * @brief
 * @version 0.1
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "led_animation.h"

int rc; // return code
// struct led_rgb rb_pixels[10];

// Function to generate a random color (RGB)

/**
 * @brief
 *
 * @return struct led_rgb
 */
static struct led_rgb random_color()
{
    struct led_rgb color;
    color.r = rand() % 256; // Random value between 0 and 255
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}

// Helper function to set LED color
/**
 * @brief Set the led color object
 *
 * @param strip
 * @param index
 * @param r
 * @param g
 * @param b
 */
static void set_led_color(struct led_strip *strip, size_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < strip->num_of_leds)
    {
        strip->led_rgb_array[index].r = r;
        strip->led_rgb_array[index].g = g;
        strip->led_rgb_array[index].b = b;
    }
}

/**
 * @brief
 *
 * @param led_strip_struct
 */
void display_pattern_all_off(struct led_strip led_strip_struct)
{
    size_t led_rgb_array_size = led_strip_struct.num_of_leds * sizeof(struct led_rgb);
    memset(led_strip_struct.led_rgb_array, 0x00, led_rgb_array_size); // clear the strip
    rc = led_strip_update_rgb(led_strip_struct.dev, led_strip_struct.led_rgb_array, led_strip_struct.num_of_leds);

    if (rc)
    {
        printk("couldn't update strip: %d\n", rc);
    }
}

/**
 * @brief
 *
 * @param pattern
 * @param len
 */
void display_pattern_mod(char *pattern, size_t len, struct led_strip led_strip_struct)
{

    for (int i = 0; i < len; i++)
    {
        size_t led_rgb_array_size = led_strip_struct.num_of_leds * sizeof(struct led_rgb);
        memset(led_strip_struct.led_rgb_array, 0x00, led_rgb_array_size); // clear the strip
        rc = led_strip_update_rgb(led_strip_struct.dev, led_strip_struct.led_rgb_array, led_strip_struct.num_of_leds);
        int index;

        // Map each character in the pattern to an index using the switch case
        switch (pattern[i])
        {
        case 'A':
            index = A;
            break;
        case 'B':
            index = B;
            break;
        case 'C':
            index = C;
            break;
        case 'D':
            index = D;
            break;
        case 'E':
            index = E;
            break;
        case 'F':
            index = F;
            break;
        case 'G':
            index = G;
            break;
        case 'H':
            index = H;
            break;
        case 'I':
            index = I;
            break;
        case 'J':
            index = J;
            break;
        case 'K':
            index = K;
            break;
        case 'L':
            index = L;
            break;
        case 'M':
            index = M;
            break;
        case 'N':
            index = N;
            break;
        case 'O':
            index = O;
            break;
        case 'P':
            index = P;
            break;
        case 'Q':
            index = Q;
            break;
        case 'R':
            index = R;
            break;
        case 'S':
            index = S;
            break;
        case 'T':
            index = T;
            break;
        case 'U':
            index = U;
            break;
        case 'V':
            index = V;
            break;
        case 'W':
            index = W;
            break;
        case 'X':
            index = X;
            break;
        case 'Y':
            index = Y;
            break;
        case 'Z':
            index = Z;
            break;
        default:
            printk("Invalid pattern character: %c\n", pattern[i]);
            continue; // Skip if invalid character
        }

        // Check if the index is valid for the LED strip size
        if (index >= 10)
        {
            printk("Invalid LED index: %d\n", index);
            continue;
        }

        // Clear the specific pixel
        memset(&led_strip_struct.led_rgb_array[index], 0x00, sizeof(struct led_rgb));

        // Set the pixel color from the colors array
        struct led_rgb rnd_clr = random_color();

        memcpy(&led_strip_struct.led_rgb_array[index], &rnd_clr, sizeof(struct led_rgb));

        // one at a time

        // Update the LED strip
        rc = led_strip_update_rgb(led_strip_struct.dev, led_strip_struct.led_rgb_array, 10);
        if (rc)
        {
            printk("Couldn't update strip: %d\n", rc);
        }

        // Sleep for the delay time
        k_sleep(DELAY_TIME);
        display_pattern_all_off(led_strip_struct);
    }
}

/**
 * @brief
 *
 * @param h
 * @param s
 * @param v
 * @return struct led_rgb
 */
struct led_rgb hsv_to_rgb(float h, float s, float v)
{
    float r = 0, g = 0, b = 0;
    int i = (int)(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6)
    {
    case 0:
        r = v, g = t, b = p;
        break;
    case 1:
        r = q, g = v, b = p;
        break;
    case 2:
        r = p, g = v, b = t;
        break;
    case 3:
        r = p, g = q, b = v;
        break;
    case 4:
        r = t, g = p, b = v;
        break;
    case 5:
        r = v, g = p, b = q;
        break;
    }

    struct led_rgb color = {
        .r = (uint8_t)(r * 255), .g = (uint8_t)(g * 255), .b = (uint8_t)(b * 255)};
    return color;
}

/**
 * @brief
 *
 * @param num_leds
 * @param led_strip_struct
 */
void rainbow_sweep(size_t num_leds, struct led_strip led_strip_struct)
{
    const struct device *strip = led_strip_struct.dev;

    float starting_hue = 0.0; // Starting hue for the rainbow effect (0 to 1 range)

    // Full cycle: run indefinitely
    while (1)
    {
        for (size_t i = 0; i < num_leds; i++)
        {
            // Calculate the hue for each LED, spreading it across the entire strip
            float hue = (starting_hue + (float)i / num_leds) -
                        floor(starting_hue + (float)i / num_leds); // Wrap around 0-1

            // Convert the hue (with full saturation and brightness) to RGB
            led_strip_struct.led_rgb_array[i] = hsv_to_rgb(hue, 1.0, 1.0); // Full saturation and brightness
        }

        // Update the LED strip with the new colors
        rc = led_strip_update_rgb(strip, led_strip_struct.led_rgb_array, num_leds);
        if (rc)
        {
            printk("Couldn't update strip: %d", rc);
        }

        // Increment the starting hue to create the sweep effect
        starting_hue += 0.005 * SWEEP_SPEED;
        if (starting_hue > 1.0)
        {
            starting_hue -= 1.0; // Wrap around the hue value
        }

        // Delay for a smooth transition
        k_msleep(SWEEP_DELAY);
    }
}

/**
 * @brief
 *
 * @param num_leds
 * @param led_strip_struct
 */
void random_glitch(size_t num_leds, struct led_strip led_strip_struct)
{
    uint32_t time_now = k_uptime_get_32();
    struct led_rgb *rb_pixels = led_strip_struct.led_rgb_array;
    struct device *strip = led_strip_struct.dev;
    // Seed the random number generator
    srand(time_now);

    // Full cycle: run indefinitely
    while (1)
    {
        // Save the current state of the LEDs so we can restore them after the glitch
        struct led_rgb original_pixels[num_leds];
        memcpy(original_pixels, rb_pixels, sizeof(struct led_rgb) * num_leds);

        // Glitch a random number of LEDs
        for (int i = 0; i < GLITCH_INTENSITY; i++)
        {
            // Pick a random LED to glitch
            int rand_led = rand() % num_leds;

            // Assign a random color to the chosen LED
            rb_pixels[rand_led] = random_color();
        }

        // Update the LED strip with the new (glitched) state
        rc = led_strip_update_rgb(strip, rb_pixels, num_leds);
        if (rc)
        {
            printk("Couldn't update strip: %d", rc);
        }

        // Short delay for the glitch to be visible
        k_msleep(GLITCH_DURATION);

        // Restore the original state of the LEDs
        memcpy(rb_pixels, original_pixels, sizeof(struct led_rgb) * num_leds);

        // Update the LED strip to restore the original state
        rc = led_strip_update_rgb(strip, rb_pixels, num_leds);
        if (rc)
        {
            printk("Couldn't update strip: %d", rc);
        }

        // Random delay before the next glitch cycle
        k_msleep(GLITCH_DELAY + (rand() % 500)); // Adds randomness to the timing
    }
}

void breathing_pattern(size_t num_leds, size_t duration_ms, struct led_strip led_strip_struct)
{
    struct device *strip = led_strip_struct.dev;
    struct led_rgb *pixels = led_strip_struct.led_rgb_array;

    for (int step = 0; step < BREATHING_STEPS; step++)
    {
        // Calculate the brightness scaling factor using a sine wave pattern
        // The sine wave oscillates between 0.0 and 1.0
        // float brightness_factor = (sin((float)step / BREATHING_STEPS * 3.14) + 1) / 2;
        // float brightness_factor =
        //	(sin(2.0 * 3.1415 * (float)step / BREATHING_STEPS) + 1) / 2;
        float brightness_factor =
            (sin((2.0 * 3.14 * (float)step / BREATHING_STEPS) - (3.14 / 2)) + 1) / 2;

        // Apply the brightness to each LED in the strip
        for (size_t i = 0; i < num_leds; i++)
        {
            pixels[i].r = (uint8_t)(0 * brightness_factor);
            pixels[i].g = (uint8_t)(0 * brightness_factor);
            pixels[i].b = (uint8_t)(250 * brightness_factor);
        }
        printk("%f\n", brightness_factor);

        // Update the LED strip with the new pixel brightness
        rc = led_strip_update_rgb(strip, pixels, num_leds);
        if (rc)
        {
            printk("Couldn't update strip: %d", rc);
        }

        // Delay for a smooth transition (you can adjust this for breathing speed)
        k_msleep(BREATHING_PERIOD);
    }
}

/**
 * @brief
 *
 * @param strip
 * @param r
 * @param g
 * @param b
 * @param tail_length
 */
void comet_effect(struct led_strip strip, uint8_t r, uint8_t g, uint8_t b, size_t tail_length)
{
    display_pattern_all_off(strip); // Clear the strip initially

    for (size_t head = 0; head < strip.num_of_leds + tail_length; head++)
    {
        display_pattern_all_off(strip); // Clear the strip initially

        // Set the tail colors
        for (size_t t = 0; t < tail_length; t++)
        {
            int pos = head - t; // Position of tail section

            if (pos >= 0 && pos < strip.num_of_leds)
            {
                // Calculate fading effect for the tail
                uint8_t fade_factor = 255 - (255 / tail_length) * t;
                set_led_color(&strip, pos, r * fade_factor / 255, g * fade_factor / 255, b * fade_factor / 255);
            }
        }

        rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
        k_msleep(25);
    }

    display_pattern_all_off(strip); // Clear the strip initially
    rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
}

/**
 * @brief
 *
 * @param strip
 */
void firework_explosion(struct led_strip strip)
{
    // Clear the strip at the start
    display_pattern_all_off(strip); // Clear the strip initially
    rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);

    // Generate a random bright color for the explosion
    struct led_rgb explosion_color = random_color();

    // Calculate the middle position of the strip (assuming symmetrical explosion)
    int center = strip.num_of_leds / 2;

    // Loop through each expansion step
    for (int step = 0; step < EXPLOSION_STEPS; step++)
    {
        // Clear the strip for the new frame
        display_pattern_all_off(strip); // Clear the strip initially

        // Calculate the brightness factor for the current step (fades as it expands)
        uint8_t fade_factor = 255 - (255 / EXPLOSION_STEPS) * step;

        // Draw explosion expanding outwards from the center
        for (int offset = 0; offset <= step; offset++)
        {
            int left_pos = center - offset;
            int right_pos = center + offset;

            // Apply fading to the explosion color for both directions
            if (left_pos >= 0)
            {
                set_led_color(&strip, left_pos,
                              explosion_color.r * fade_factor / 255,
                              explosion_color.g * fade_factor / 255,
                              explosion_color.b * fade_factor / 255);
            }

            if (right_pos < strip.num_of_leds)
            {
                set_led_color(&strip, right_pos,
                              explosion_color.r * fade_factor / 255,
                              explosion_color.g * fade_factor / 255,
                              explosion_color.b * fade_factor / 255);
            }
        }

        // Update the LED strip and add delay for the next expansion step
        rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
        k_msleep(20);
    }

    // Clear the strip at the end of the explosion
    display_pattern_all_off(strip); // Clear the strip initially
    rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
}

/**
 * @brief
 *
 * @param strip
 */
void fire_flicker(struct led_strip strip)
{
    while (true)
    {
        for (size_t i = 0; i < strip.num_of_leds; i++)
        {
            // Randomly decide on flickering intensity
            uint8_t flicker = rand() % 100;           // Random value to control flickering
            uint8_t r = flicker + 150;                // Red with base brightness
            uint8_t g = (flicker < 50) ? flicker : 0; // Random green flicker
            uint8_t b = 0;                            // No blue for fire

            set_led_color(&strip, i, b, r, g);
            rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
        }
        rc = led_strip_update_rgb(strip.dev, strip.led_rgb_array, strip.num_of_leds);
        k_msleep(50); // Adjust flicker speed
    }
}