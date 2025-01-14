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

enum layer_names {
  _COLEMAK,
  _DVORAK,
  _QWERTY,
  _FSYM,
  _NUMNAV,
  _ADJUST,
  _CTRL,
  _NUMPAD
};

#define NUMNAV MO(_NUMNAV)
#define FSYM MO(_FSYM)
#define CTL_LYR MO(_CTRL)
#define NUMPAD MO(_NUMPAD)
#define CLMK DF(_COLEMAK)
#define DVRK DF(_DVORAK)
#define QWRT DF(_QWERTY)
#define _____ KC_TRANSPARENT
#define C_A_D LCA(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_Q       , KC_W       , KC_F       , KC_P       , KC_G       , KC_J       , KC_L       , KC_U       , KC_Y       , KC_SCLN    , KC_BSPC    ,
        CTL_LYR    , KC_A       , KC_R       , KC_S       , KC_T       , KC_D       , KC_H       , KC_N       , KC_E       , KC_I       , KC_O       , KC_ENT     ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_K       , KC_M       , KC_COMMA   , KC_DOT     , KC_SLSH    , KC_RSFT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , NUMNAV     , KC_SPC     , KC_SPC     , FSYM       , KC_GRAVE   , KC_RALT    , KC_RGUI    , KC_RCTL
        ),
    [_DVORAK] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_QUOTE   , KC_COMMA   , KC_DOT     , KC_P       , KC_Y       , KC_F       , KC_G       , KC_C       , KC_R       , KC_L       , KC_BSPC    ,
        CTL_LYR    , KC_A       , KC_O       , KC_E       , KC_U       , KC_I       , KC_D       , KC_H       , KC_T       , KC_N       , KC_S       , KC_ENT     ,
        KC_LSFT    , KC_SCLN    , KC_Q       , KC_J       , KC_K       , KC_X       , KC_B       , KC_M       , KC_W       , KC_V       , KC_Z       , KC_RSFT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , NUMNAV     , KC_SPC     , KC_SPC     , FSYM       , KC_GRAVE   , KC_RALT    , KC_RGUI    , KC_RCTL
        ),
    [_QWERTY] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       , KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC    ,
        CTL_LYR    , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       , KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , KC_ENT     ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , KC_RSFT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , NUMNAV     , KC_SPC     , KC_SPC     , FSYM       , KC_GRAVE   , KC_RALT    , KC_RGUI    , KC_RCTL
        ),
    [_FSYM] = LAYOUT_ortho_4x12(
        _____      , KC_EXLM    , KC_AT      , KC_HASH    , KC_DLR     , KC_PERC    , KC_CIRC    , KC_AMPR    , KC_ASTR    , KC_LPRN    , KC_RPRN    , KC_BSLS    ,
        _____      , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      , KC_F6      , KC_UNDS    , KC_PLUS    , KC_LCBR    , KC_RCBR    , KC_QUOTE   ,
        _____      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11     , KC_F12     , KC_MINS    , KC_EQUAL   , KC_LBRC    , KC_RBRC    , KC_SLSH    ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____
    ),
    [_NUMNAV] = LAYOUT_ortho_4x12(
        _____      , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       , KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , _____      ,
        _____      , _____      , _____      , MS_WHLU    , _____      , KC_PGUP    , MS_WHLU    , MS_BTN1    , MS_UP      , MS_BTN2    , _____      , _____      ,
        _____      , _____      , MS_WHLL    , MS_WHLD    , MS_WHLR    , KC_PGDN    , MS_WHLD    , MS_LEFT    , MS_DOWN    , MS_RGHT    , _____      , _____      ,
        _____      , KC_ACL0    , _____      , _____      , _____      , _____      , _____      , _____      , MS_BTN3    , _____      , KC_ACL0    , _____
    ),
    [_ADJUST] = LAYOUT_ortho_4x12(
        QK_BOOT    , UG_TOGG    , UG_HUEU    , UG_SATU    , UG_VALU    , _____      , _____      , _____      , _____      , _____      , _____      , DB_TOGG    ,
        _____      , UG_NEXT    , UG_HUED    , UG_SATD    , UG_VALD    , AG_NORM    , AG_SWAP    , _____      , _____      , _____      , _____      , _____      ,
        _____      , BL_TOGG    , BL_DOWN    , BL_UP      , BL_BRTG    , _____      , _____      , _____      , _____      , _____      , _____      , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____
    ),
    [_CTRL] = LAYOUT_ortho_4x12(
        C_A_D      , CLMK       , DVRK       , QWRT       , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_UP      , KC_NO      , KC_PSCR    , KC_PAUSE   ,
        _____      , KC_NO      , KC_NO      , KC_VOLU    , KC_MUTE    , KC_NO      , KC_NO      , KC_LEFT    , KC_DOWN    , KC_RGHT    , KC_NO      , _____      ,
        _____      , KC_NO      , KC_MPRV    , KC_VOLD    , KC_MNXT    , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , _____      ,
        _____      , _____      , _____      , _____      , NUMPAD     , KC_MPLY    , KC_MPLY    , _____      , _____      , _____      , _____      , _____
    ),
    [_NUMPAD] = LAYOUT_ortho_4x12(
        _____      , _____      , KC_INS     , KC_HOME    , KC_PGUP    , _____      , KC_PSLS    , KC_KP_7    , KC_KP_8    , KC_KP_9    , KC_PMNS    , _____      ,
        _____      , _____      , KC_DEL     , KC_END     , KC_PGDN    , _____      , KC_PAST    , KC_KP_4    , KC_KP_5    , KC_KP_6    , KC_PPLS    , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_KP_1    , KC_KP_2    , KC_KP_3    , KC_PAST    , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_KP_0    , KC_KP_0    , KC_PDOT    , KC_PENT    , _____
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _FSYM, _NUMNAV, _ADJUST);
}
