/* Copyright 2021 James Young (@noroadsleft)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum {
    TD_E_ACCENT_E,
    TD_A_ACCENT_A,
    TD_O_ACCENT_O,
    TD_U_ACCENT_U,
};

/*
 * NB: This section is only working as expected on macOS with a US keyboard layout
 *
 * This function will take a key definition along with the data passed by the
 * tap dance function and send an accented letter to the computer when pressed twice fast.
 * 
 * On macOS, you can get accented letters, while using US layout, by pressing `option` + `e` and then press `e` again.
 */
void td_accent_letter_finished(qk_tap_dance_state_t *state, void *user_data, int kc) {
    if (state->count == 1) {
        register_code(kc);
    } else {
        tap_code16(LALT(KC_GRV));
        register_code(kc);
    }
}

void td_accent_letter_reset(qk_tap_dance_state_t *state, void *user_data, int kc) {
    if (state->count == 1) {
        unregister_code(kc);
    } else {
        unregister_code(kc);
    }
}

void e_accent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_finished(state, user_data, KC_E);
}

void e_accent_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_reset(state, user_data, KC_E);
}

void a_accent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_finished(state, user_data, KC_A);
}

void a_accent_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_reset(state, user_data, KC_A);
}

void u_accent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_finished(state, user_data, KC_U);
}

void u_accent_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_reset(state, user_data, KC_U);
}

void o_accent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_finished(state, user_data, KC_O);
}

void o_accent_reset(qk_tap_dance_state_t *state, void *user_data) {
    td_accent_letter_reset(state, user_data, KC_O);
}

//  Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_E_ACCENT_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_accent_finished, e_accent_reset),
    [TD_O_ACCENT_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o_accent_finished, o_accent_reset),
    [TD_U_ACCENT_U] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u_accent_finished, u_accent_reset),
    [TD_A_ACCENT_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_accent_finished, a_accent_reset),
};

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_TAB,   KC_Q,              KC_W,    TD(TD_E_ACCENT_E),    KC_R,    KC_T,    KC_Y,    TD(TD_U_ACCENT_U),    KC_I,    TD(TD_O_ACCENT_O),    KC_P,    KC_BSPC,
        KC_ESC,   TD(TD_A_ACCENT_A), KC_S,    KC_D,                 KC_F,    KC_G,    KC_H,    KC_J,                 KC_K,    KC_L,                 KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,              KC_X,    KC_C,                 KC_V,    KC_B,    KC_N,    KC_M,                 KC_COMM, KC_DOT,               KC_SLSH, KC_ENT,
        KC_CAPS,  KC_LCTL,           KC_LALT, KC_LGUI,              MO(1),   KC_SPC,  KC_SPC,  MO(2),                KC_UP,   KC_LEFT,              KC_DOWN, KC_RGHT
    ),
    [_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        RESET,   _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    )
};
