// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// NOTE:
// - If I need to enter the bootloader, add the QK_BOOT keycode
// - Maybe use TT(layer) or layer lock key on layers such as numpad
//
// TEST:
// - Function layer
// - Mouse
//
// TODO:
// - Setup External QMK Userspace
// - Layers
//  - Gaming
// - Missing functionality (macros?)
//  - Close < on hold
//  - Close ( on hold
//  - Close { on hold
//  - Close [ on hold
//  - Close " on hold
// - Repeat key
// - Alt-repeat
// - Add Capsword

#include QMK_KEYBOARD_H

// https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_danish.h
#include "keymap_danish.h"

enum layer_names {
    _BASE = 0,
    _NUMPAD = 1,
    _SYMBOLS = 2,
    _NAVIGTION = 3,
    _FUNCTION = 4,
    _MOUSE = 5,
    _GAMING = 6,
};

enum custom_keycodes {
    SEARCH_IN_NEWTAB = SAFE_RANGE,
};

// -------------------
// Combo definitions
// -------------------
enum combos {
    OE_LATIN,
};

const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};

combo_t key_combos[] = {
    [OE_LATIN] = COMBO(oe_combo, DK_OSTR),
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

enum {
    TD_CP_CTRL,
    TD_PS_LSFT,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_CP_CTRL] = ACTION_TAP_DANCE_TAP_HOLD(C(KC_C), KC_LCTL),
    [TD_PS_LSFT] = ACTION_TAP_DANCE_TAP_HOLD(C(KC_V), KC_LSFT),
};

// --------------------
// Tapping term per key
// --------------------
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case <key>:
        //     return TAPPING_TERM +/- x
        //     // or
        //     return x
        default:
            return TAPPING_TERM;
    }
}

// -------------------
// Process Record User
// -------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_CP_CTRL):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
        case TD(TD_PS_LSFT):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
        case SEARCH_IN_NEWTAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ct") SS_DELAY(200) SS_LCTL("lv") "\n");
            };
            break;
    };
    return true;
};

// -------------------
// Keymaps
// -------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   *  ASDF JKLÆ are mod taps:
   *  Index:   Shift
   *  Middle:  Control
   *  Ring:    Mod
   *  Pinky:   Alt
   *
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ ⌀ │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ Å │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ Æ │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │Cap│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ - │ ⌀ │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │Esc├───┐           ┌───┤Del│
   *                └───┤Spc├───┐   ┌───┤Bsp├───┘
   *                    └───┤Tab│   │Ret├───┘
   *                        └───┘   └───┘
   */
  [_BASE] = LAYOUT_split_3x6_3(
    KC_NO,   KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,                        KC_Y, KC_U,        KC_I,        KC_O,        KC_P,         DK_ARNG,
    KC_NO,   ALT_T(KC_A), GUI_T(KC_S), CTL_T(KC_D), SFT_T(KC_F), KC_G,                        KC_H, SFT_T(KC_J), CTL_T(KC_K), GUI_T(KC_L), ALT_T(DK_AE), KC_NO,
    KC_CAPS, KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,                        KC_N, KC_M,        KC_COMM,     KC_DOT,      DK_MINS,      KC_NO,
               LT(_MOUSE, KC_ESC), LT(_NAVIGTION, KC_SPC), LT(_NUMPAD, KC_TAB),      KC_ENT, LT(_SYMBOLS, KC_BSPC), LT(_FUNCTION, KC_DEL)
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ 󰇚 │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ = │       │ / │ 6 │ 7 │ 9 │ * │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ▽ │ ▽ │ ▽ │ ▽ │ % │       │ + │ 3 │ 4 │ 5 │ 0 │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ⌀ │ ⌀ │ ( │ ) │ ^ │       │ - │ 1 │ 2 │ 3 │ , │ ⌀ │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │ ▽ ├───┐           ┌───┤ ▽ │
   *                └───┤ ▽ ├───┐   ┌───┤ ▽ ├───┘
   *                    └───┤ ▽ │   │ ▽ ├───┘
   *                        └───┘   └───┘
   */
  [_NUMPAD] = LAYOUT_split_3x6_3(
    QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   DK_EQL,                           DK_SLSH, KC_7, KC_8, KC_9, DK_ASTR, KC_NO,
    KC_NO,   _______, _______, _______, _______, DK_PERC,                          DK_PLUS, KC_4, KC_5, KC_6, KC_0,    KC_NO,
    KC_NO,   KC_NO,   KC_NO,   DK_LPRN, DK_RPRN, DK_CIRC,                          DK_MINS, KC_1, KC_2, KC_3, KC_PCMM, KC_NO,
                                          _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ ⌀ │ ´ │ ' │ # │ % │ - │       │ ` │ { │ @ │ } │ ¨ │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ $ │ \ │ ! │ / │ = │       │ " │ ( │ ? │ ) │ * │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ § │ < │ & │ > │ + │       │ ~ │ [ │ | │ ] │ ^ │ ⌀ │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │ ▽ ├───┐           ┌───┤ ▽ │
   *                └───┤ ▽ ├───┐   ┌───┤ ▽ ├───┘
   *                    └───┤ ▽ │   │ ▽ ├───┘
   *                        └───┘   └───┘
   * TODO: Missing features:
   * - Close < on hold
   * - Close ( on hold
   * - Close { on hold
   * - Close [ on hold
   * - Close " on hold
   *
   */
  [_SYMBOLS] = LAYOUT_split_3x6_3(
    KC_NO, DK_ACUT, DK_QUOT, DK_HASH, DK_PERC, DK_MINS,                         DK_GRV,  DK_LCBR, DK_AT,   DK_RCBR, DK_DIAE, KC_NO,
    KC_NO, DK_DLR,  DK_BSLS, DK_EXLM, DK_SLSH, DK_EQL,                          DK_DQUO, DK_LPRN, DK_QUES, DK_RPRN, DK_ASTR, KC_NO,
    KC_NO, DK_SECT, DK_LABK, DK_AMPR, DK_RABK, DK_PLUS,                         DK_TILD, DK_LBRC, DK_PIPE, DK_RBRC, DK_CIRC, KC_NO,
                                        _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ ⌀ │ ⌀ │ ★ │ ✖ │  │ 󰑓 │       │ ↖ │ ⇟ │ ⇞ │ ↘ │ ⌀ │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ▣ │ ✂ │ ⧉ │ ⎘ │ ↶ │       │ ← │ ↓ │ ↑ │ → │ ⌀ │ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ⌀ │ ⌀ │ ⇤ │ ⇥ │ ↷ │       │ ⌀ │ ⟸ │ ⟹ │ ⌀ │ ⌀ │ ⌀ │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │   ├───┐           ┌───┤   │
   *                └───┤   ├───┐   ┌───┤   ├───┘
   *                    └───┤   │   │   ├───┘
   *                        └───┘   └───┘
   * TODO: Missing features:
   * - Shift when holding paste button
   * - Ctrl when holding copy button
   *
   */
  [_NAVIGTION] = LAYOUT_split_3x6_3(
    KC_NO, KC_NO, SEARCH_IN_NEWTAB, C(KC_W),        C(KC_T),        LCS(KC_T),                       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO, KC_NO,
    KC_NO, C(KC_A), C(KC_X),        TD(TD_CP_CTRL), TD(TD_PS_LSFT), C(KC_Z),                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO,            LCS(KC_TAB),    C(KC_TAB),      C(KC_Y),                         KC_NO, KC_WBAK, KC_WFWD, KC_NO, KC_NO, KC_NO,
                                                        _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ ⌀ │ ⌀ │  │ 󰒮 │ 󰒭 │ 󰏤 │       │ ⌀ │ F7│ F8│ F9│F12│ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │SFT│  │ 󰝞 │ 󰝝 │ 󰝟 │       │ ⌀ │ F4│ F5│ F6│F11│ ⌀ │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ⌀ │  │ 󰃞 │ 󰃠 │ ⌀ │       │ ⌀ │ F1│ F2│ F3│F10│ ⌀ │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │   ├───┐           ┌───┤   │
   *                └───┤   ├───┐   ┌───┤   ├───┘
   *                    └───┤   │   │   ├───┘
   *                        └───┘   └───┘
   *
   * Missing features:
   * - Navigate to gaming layer
   *
   */
  [_FUNCTION] = LAYOUT_split_3x6_3(
    // |- This is the gaming key
    KC_NO, KC_NO,   S(KC_PSCR), KC_MPRV, KC_MNXT, KC_MPLY,                       KC_NO, KC_F7, KC_F8, KC_F9, KC_F12, KC_NO,
    KC_NO, KC_LSFT, KC_PSCR,    KC_VOLD, KC_VOLU, KC_MUTE,                       KC_NO, KC_F4, KC_F5, KC_F6, KC_F11, KC_NO,
    KC_NO, KC_NO,   C(KC_PSCR), KC_BRID, KC_BRIU, KC_NO,                         KC_NO, KC_F1, KC_F2, KC_F3, KC_F10, KC_NO,
                                        _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │       │   │   │   │   │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │       │   │   │   │   │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │ ⌀ │       │   │   │   │   │   │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │   ├───┐           ┌───┤   │
   *                └───┤   ├───┐   ┌───┤   ├───┘
   *                    └───┤   │   │   ├───┘
   *                        └───┘   └───┘
   */
  [_MOUSE] = LAYOUT_split_3x6_3(
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                         MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                         MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO, KC_NO,
   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                         KC_NO,   MS_ACL0, MS_ACL1, MS_ACL2, KC_NO, KC_NO,
                            _______, _______, _______,      MS_BTN2, MS_BTN1, MS_BTN3
  ),
};

  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │   │   │   │   │   │   │       │   │   │   │   │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │   │   │   │   │   │       │   │   │   │   │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │   │   │   │   │   │       │   │   │   │   │   │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │   ├───┐           ┌───┤   │
   *                └───┤   ├───┐   ┌───┤   ├───┘
   *                    └───┤   │   │   ├───┘
   *                        └───┘   └───┘
   */
  // [] = LAYOUT_split_3x6_3(
  //   , , , , , ,                         , , , , , ,
  //   , , , , , ,                         , , , , , ,
  //   , , , , , ,                         , , , , , ,
  //                                       _______, _______, _______,      _______, _______, _______
  //),
