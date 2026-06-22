/*
 * Copyright (c) 2026 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/settings/settings.h>

#include <zmk/power_runtime.h>

struct zmk_power_runtime_settings_data {
    uint32_t idle_timeout_ms;
    uint32_t sleep_timeout_ms;
} __packed;

static const struct zmk_power_runtime_settings_data power_defaults = {
    .idle_timeout_ms = CONFIG_ZMK_IDLE_TIMEOUT,
#if IS_ENABLED(CONFIG_ZMK_SLEEP)
    .sleep_timeout_ms = CONFIG_ZMK_IDLE_SLEEP_TIMEOUT,
#else
    .sleep_timeout_ms = 0,
#endif
};

static struct zmk_power_runtime_settings_data power_state = {
    .idle_timeout_ms = CONFIG_ZMK_IDLE_TIMEOUT,
#if IS_ENABLED(CONFIG_ZMK_SLEEP)
    .sleep_timeout_ms = CONFIG_ZMK_IDLE_SLEEP_TIMEOUT,
#else
    .sleep_timeout_ms = 0,
#endif
};

#if IS_ENABLED(CONFIG_SETTINGS)
static void zmk_power_runtime_save_state_work(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(power_runtime_save_work, zmk_power_runtime_save_state_work);
#endif

int zmk_power_runtime_get_state(struct zmk_power_runtime_state *out_state) {
    if (!out_state) {
        return -EINVAL;
    }

    out_state->idle_timeout_ms = power_state.idle_timeout_ms;
    out_state->sleep_timeout_ms = power_state.sleep_timeout_ms;
    return 0;
}

uint32_t zmk_power_runtime_get_idle_timeout_ms(void) { return power_state.idle_timeout_ms; }

uint32_t zmk_power_runtime_get_sleep_timeout_ms(void) { return power_state.sleep_timeout_ms; }

int zmk_power_runtime_set_idle_timeout_ms(uint32_t timeout_ms) {
    power_state.idle_timeout_ms = timeout_ms;
    return 0;
}

int zmk_power_runtime_set_sleep_timeout_ms(uint32_t timeout_ms) {
    power_state.sleep_timeout_ms = timeout_ms;
    return 0;
}

#if IS_ENABLED(CONFIG_SETTINGS)
static int power_runtime_settings_set(const char *name, size_t len, settings_read_cb read_cb,
                                      void *cb_arg) {
    const char *next;

    if (settings_name_steq(name, "state", &next) && !next) {
        if (len != sizeof(power_state)) {
            return -EINVAL;
        }

        int rc = read_cb(cb_arg, &power_state, sizeof(power_state));
        return rc >= 0 ? 0 : rc;
    }

    return -ENOENT;
}

SETTINGS_STATIC_HANDLER_DEFINE(power_runtime, "power/runtime", NULL, power_runtime_settings_set,
                               NULL, NULL);

static void zmk_power_runtime_save_state_work(struct k_work *work) {
    ARG_UNUSED(work);
    settings_save_one("power/runtime/state", &power_state, sizeof(power_state));
}
#endif

int zmk_power_runtime_save_state(void) {
#if IS_ENABLED(CONFIG_SETTINGS)
    int ret =
        k_work_reschedule(&power_runtime_save_work, K_MSEC(CONFIG_ZMK_SETTINGS_SAVE_DEBOUNCE));
    return MIN(ret, 0);
#else
    return 0;
#endif
}

int zmk_power_runtime_settings_reset(void) {
    power_state = power_defaults;

#if IS_ENABLED(CONFIG_SETTINGS)
    int ret = settings_delete("power/runtime/state");
    if (ret < 0 && ret != -ENOENT) {
        return ret;
    }
#endif

    return 0;
}
