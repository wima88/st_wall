

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include "led_animation.h"
#include <zephyr/logging/log.h>

#define MY_STACK_SIZE 1024
#define MY_PRIORITY 5
#define LOG_LEVEL 4
LOG_MODULE_REGISTER(thread_led);

#define STRIP_NODE DT_ALIAS(led_strip)

struct device *const strip = DEVICE_DT_GET(STRIP_NODE);
#define STRIP_NUM_PIXELS DT_PROP(DT_ALIAS(led_strip), chain_length)

struct led_rgb pixels[STRIP_NUM_PIXELS];
K_EVENT_DEFINE(bt_events);

void my_entry_point(int unused1, int unused2, int unused3)
{

    struct led_strip strip_srct = {
        .dev = strip,
        .num_of_leds = STRIP_NUM_PIXELS,
        .led_rgb_array = pixels};

    // uint32_t events;

    if (device_is_ready(strip))
    {
        LOG_INF("Found LED strip device %s", strip->name);
    }
    else
    {
        LOG_ERR("LED strip device %s is not ready", strip->name);
        return;
    }

    display_pattern_all_off(strip_srct);
    while (1)
    {
        /* run glish in background*/
        // random_glitch(26, strip_srct);

        /* TESTING ONLY */
        // events = k_event_wait(&bt_events, 0x002, false, K_MSEC(100));
        // if (events == 0x002)
        // {
        //     breathing_pattern(STRIP_NUM_PIXELS, 500, strip_srct);
        //     printk("No input devices are available!");
        // }

        rainbow_sweep(26, strip_srct);
        // comet_effect(strip_srct, 0, 0, 255, 7);
        // comet_effect(strip_srct, 0, 255, 0, 7);
        // comet_effect(strip_srct, 255, 0, 0, 7);
        // firework_explosion(strip_srct);
        // breathing_pattern(STRIP_NUM_PIXELS, 1000, strip_srct);
        //fire_flicker(strip_srct);
        k_msleep(500);
    }
}

K_THREAD_DEFINE(my_tid, MY_STACK_SIZE,
                my_entry_point, NULL, NULL, NULL,
                MY_PRIORITY, 0, 0);