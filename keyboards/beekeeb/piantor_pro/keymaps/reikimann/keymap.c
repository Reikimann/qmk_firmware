// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_danish.h
#include "keymap_danish.h"

enum layer_names {
    _BASE = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *
     *  ASDF JKLÆ are mod taps:
     *  Index:   Shift
     *  Middle:  Control
     *  Ring:    Mod
     *  Pinky:   Alt
     *
     *  ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
     *  │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ Å │
     *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     *  │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ Æ │ ' │
     *  ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
     *  │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
     *  └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
     *                ┌───┐                   ┌───┐
     *                │Esc├───┐           ┌───┤Del│
     *                └───┤Spc├───┐   ┌───┤Bsp├───┘
     *                    └───┤Tab│   │Ret├───┘
     *                        └───┘   └───┘
     */
    [_BASE] = LAYOUT_split_3x6_3(
      XXXXXXX,        KC_Q,        KC_W,        KC_E,        KC_R,    KC_T,                        KC_Y,        KC_U,        KC_I,        KC_O,         KC_P, DK_ARNG,
      XXXXXXX, ALT_T(KC_A), GUI_T(KC_S), CTL_T(KC_D), SFT_T(KC_F),    KC_G,                        KC_H, SFT_T(KC_J), CTL_T(KC_K), GUI_T(KC_L), ALT_T(DK_AE), XXXXXXX,
      KC_CAPS,        KC_Z,        KC_X,        KC_C,        KC_V,    KC_B,                        KC_N,        KC_M,     KC_COMM,      KC_DOT,     KC_MINUS, XXXXXXX,
                                                            KC_ESC, KC_SPC, KC_TAB,      KC_ENT, KC_BSPC, KC_DEL
  )
};
