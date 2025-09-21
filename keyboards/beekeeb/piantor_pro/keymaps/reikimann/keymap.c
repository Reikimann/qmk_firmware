// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
//
// NOTE:
// - If I need to enter the bootloader, add the QK_BOOT keycode
// - Maybe use TT(layer) or layer lock key on layers such as numpad
//
// TODO:
// - Setup External QMK Userspace
// - Add Capsword
// - Layers
//  - Function
//  - Mouse
//  - Gaming
// - Missing functionality (macros?)
//  - Close < on hold
//  - Close ( on hold
//  - Close { on hold
//  - Close [ on hold
//  - Close " on hold

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
    SEARCH_COPIED_IN_NEWTAB = SAFE_RANGE,
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

// -------------------
// Process Record User
// -------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SEARCH_COPIED_IN_NEWTAB:
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
   *  │   │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ Å │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ Æ │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │Cap│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ - │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │Esc├───┐           ┌───┤Del│
   *                └───┤Spc├───┐   ┌───┤Bsp├───┘
   *                    └───┤Tab│   │Ret├───┘
   *                        └───┘   └───┘
   */
  [_BASE] = LAYOUT_split_3x6_3(
    XXXXXXX, KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,                        KC_Y, KC_U,        KC_I,        KC_O,        KC_P,         DK_ARNG,
    XXXXXXX, ALT_T(KC_A), GUI_T(KC_S), CTL_T(KC_D), SFT_T(KC_F), KC_G,                        KC_H, SFT_T(KC_J), CTL_T(KC_K), GUI_T(KC_L), ALT_T(DK_AE), XXXXXXX,
    KC_CAPS, KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,                        KC_N, KC_M,        KC_COMM,     KC_DOT,      DK_MINS,      XXXXXXX,
                              KC_ESC, LT(_NAVIGTION, KC_SPC), LT(_NUMPAD, KC_TAB),      KC_ENT, LT(_SYMBOLS, KC_BSPC), KC_DEL
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │   │   │   │   │   │ = │       │ / │ 6 │ 7 │ 9 │ * │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │ ▽ │ ▽ │ ▽ │ ▽ │ % │       │ + │ 3 │ 4 │ 5 │ - │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │   │   │ ( │ ) │ ^ │       │ 0 │ 1 │ 2 │ 3 │ , │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │ ▽ ├───┐           ┌───┤ ▽ │
   *                └───┤ ▽ ├───┐   ┌───┤ ▽ ├───┘
   *                    └───┤ ▽ │   │ ▽ ├───┘
   *                        └───┘   └───┘
   */
  [_NUMPAD] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DK_EQL,                           DK_SLSH, KC_7, KC_8, KC_9, DK_ASTR, XXXXXXX,
    XXXXXXX, _______, _______, _______, _______, DK_PERC,                          DK_PLUS, KC_4, KC_5, KC_6, DK_MINS, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, DK_LPRN, DK_RPRN, DK_CIRC,                          KC_0,    KC_1, KC_2, KC_3, KC_PCMM, XXXXXXX,
                                          _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │   │ ´ │ ' │ # │ % │ - │       │ ` │ { │ @ │ } │ ¨ │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │ $ │ \ │ ! │ / │ = │       │ " │ ( │ ? │ ) │ * │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │ § │ < │ & │ > │ + │       │ ~ │ [ │ | │ ] │ ^ │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │ ▽ ├───┐           ┌───┤ ▽ │
   *                └───┤ ▽ ├───┐   ┌───┤ ▽ ├───┘
   *                    └───┤ ▽ │   │ ▽ ├───┘
   *                        └───┘   └───┘
   * Missing features:
   * - Close < on hold
   * - Close ( on hold
   * - Close { on hold
   * - Close [ on hold
   * - Close " on hold
   *
   */
  [_SYMBOLS] = LAYOUT_split_3x6_3(
    XXXXXXX, DK_ACUT, DK_QUOT, DK_HASH, DK_PERC, DK_MINS,                         DK_GRV,  DK_LCBR, DK_AT,   DK_RCBR, DK_DIAE, XXXXXXX,
    XXXXXXX, DK_DLR,  DK_BSLS, DK_EXLM, DK_SLSH, DK_EQL,                          DK_DQUO, DK_LPRN, DK_QUES, DK_RPRN, DK_ASTR, XXXXXXX,
    XXXXXXX, DK_SECT, DK_LABK, DK_AMPR, DK_RABK, DK_PLUS,                         DK_TILD, DK_LBRC, DK_PIPE, DK_RBRC, DK_CIRC, XXXXXXX,
                                        _______, _______, _______,      _______, _______, _______
  ),
  /*
   *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
   *  │   │   │ ★ │ ✖ │ ＋│ ↺ │       │ ↖ │ ⇟ │ ⇞ │ ↘ │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │ ▣ │ ✂ │ ⧉ │ ⎘ │ ↶ │       │ ← │ ↓ │ ↑ │ → │   │   │
   *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
   *  │   │   │   │ ⇤ │ ⇥ │ ↷ │       │   │ ⟸ │ ⟹ │   │   │   │
   *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
   *                ┌───┐                   ┌───┐
   *                │   ├───┐           ┌───┤   │
   *                └───┤   ├───┐   ┌───┤   ├───┘
   *                    └───┤   │   │   ├───┘
   *                        └───┘   └───┘
   */
  [_NAVIGTION] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, SEARCH_COPIED_IN_NEWTAB, C(KC_W),     C(KC_T),   LCS(KC_T),                       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
    XXXXXXX, C(KC_A), C(KC_X),                 C(KC_C),     C(KC_V),   C(KC_Z),                         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,                 LCS(KC_TAB), C(KC_TAB), C(KC_Y),                         XXXXXXX, KC_WBAK, KC_WFWD, XXXXXXX, XXXXXXX, XXXXXXX,
                                               _______, _______, _______,      _______, _______, _______
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
