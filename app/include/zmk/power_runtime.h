/*
 * Copyright (c) 2026 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

struct zmk_power_runtime_state {
    uint32_t idle_timeout_ms;
    uint32_t sleep_timeout_ms;
};

int zmk_power_runtime_get_state(struct zmk_power_runtime_state *out_state);
uint32_t zmk_power_runtime_get_idle_timeout_ms(void);
uint32_t zmk_power_runtime_get_sleep_timeout_ms(void);
int zmk_power_runtime_set_idle_timeout_ms(uint32_t timeout_ms);
int zmk_power_runtime_set_sleep_timeout_ms(uint32_t timeout_ms);
int zmk_power_runtime_save_state(void);
int zmk_power_runtime_settings_reset(void);
