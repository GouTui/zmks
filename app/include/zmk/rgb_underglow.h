/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct zmk_led_hsb {
    uint16_t h;
    uint8_t s;
    uint8_t b;
};

struct zmk_rgb_low_battery_indicator_state {
    bool enabled;
    uint32_t color;
    uint8_t key_pos;
    uint32_t period_ms;
    uint8_t threshold_pct;
    uint16_t flash_duration_ms;
    bool demo_enabled;
};

int zmk_rgb_underglow_toggle(void);
int zmk_rgb_underglow_get_state(bool *state);
int zmk_rgb_underglow_on(void);
int zmk_rgb_underglow_off(void);
int zmk_rgb_underglow_transient_on(void);
int zmk_rgb_underglow_transient_off(void);
int zmk_rgb_underglow_cycle_effect(int direction);
int zmk_rgb_underglow_calc_effect(int direction);
int zmk_rgb_underglow_select_effect(int effect);
struct zmk_led_hsb zmk_rgb_underglow_calc_hue(int direction);
struct zmk_led_hsb zmk_rgb_underglow_calc_sat(int direction);
struct zmk_led_hsb zmk_rgb_underglow_calc_brt(int direction);
int zmk_rgb_underglow_change_hue(int direction);
int zmk_rgb_underglow_change_sat(int direction);
int zmk_rgb_underglow_change_brt(int direction);
int zmk_rgb_underglow_change_spd(int direction);
struct zmk_led_hsb zmk_rgb_underglow_calc_rgb_channel(int channel, int direction);
int zmk_rgb_underglow_change_rgb_channel(int channel, int direction);
int zmk_rgb_underglow_set_hsb(struct zmk_led_hsb color);
int zmk_rgb_underglow_show_battery_level(void);

struct zmk_led_hsb zmk_rgb_underglow_get_hsb(void);
int zmk_rgb_underglow_get_effect(void);
int zmk_rgb_underglow_get_speed(void);
int zmk_rgb_underglow_set_speed(int speed);
int zmk_rgb_underglow_get_effect_count(void);
int zmk_rgb_underglow_save_state(void);
int zmk_rgb_low_battery_indicator_get_state(struct zmk_rgb_low_battery_indicator_state *out_state);
int zmk_rgb_low_battery_indicator_set_enabled(bool enabled);
int zmk_rgb_low_battery_indicator_set_key_pos(uint8_t key_pos);
int zmk_rgb_low_battery_indicator_set_period_ms(uint32_t period_ms);
int zmk_rgb_low_battery_indicator_set_color(uint32_t color);
int zmk_rgb_low_battery_indicator_set_threshold_pct(uint32_t threshold_pct);
int zmk_rgb_low_battery_indicator_set_flash_duration_ms(uint32_t flash_duration_ms);
int zmk_rgb_low_battery_indicator_set_demo_enabled(bool demo_enabled);
int zmk_rgb_low_battery_indicator_save(void);
int zmk_rgb_low_battery_indicator_settings_reset(void);
