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
  _BASE,
  _QWERTY = _BASE,
  _COLEMAK,
  _DVORAK,
  _SYMBLS,
  _RAISE = _SYMBLS,
  _NUMBRS,
  _LOWER = _NUMBRS,
  _FEATURS,
  _ADJUST = _FEATURS,
  _NUMPAD,
  _TABULA,
  _MOUSY,
};

#define LOWER MO(_NUMBRS)
#define RAISE MO(_SYMBLS)
#define NUMPAD MO(_NUMPAD)
#define CLMK DF(_COLEMAK)
#define DVRK DF(_DVORAK)
#define QWRT DF(_QWERTY)
#define _____ KC_TRANSPARENT
#define C_A_D LCA(KC_DEL)
#define TBLA LT(_TABULA, KC_TAB)
// Declare stored memory config
typedef union {
    uint32_t raw;
    struct {
        bool    do_wakeup_animation : 1;
        uint8_t rgbcon_tracker : 8;
        bool    do_wakeup_audio : 1;
    };
} user_config_t;

user_config_t user_config;
uint8_t mod_state = 0;

enum custom_keycodes {
    MO_BASE = SAFE_RANGE,
    MO_SYMBLS,
    MO_NUMBRS,
    MO_FEATURS,
    QWERTY,
    COLEMAK,
    DVORAK,
    BACKLIT,
    ALT_TAB,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    KC_REDO,
    KC_SAVE,
    KC_SLCTALL,
    KC_ALTF4,
    KC_KILL,
    KC_LCUT,
    KC_LCOPY,
    KC_NXTAB,
    KC_PRVTAB,
};

enum combo_events { ZC_COPY, XV_PASTE };

const uint16_t PROGMEM copy_combo[]  = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[] = {
    [ZC_COPY]  = COMBO_ACTION(copy_combo),
    [XV_PASTE] = COMBO_ACTION(paste_combo),
};

bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_Q       , KC_W       , KC_E       , KC_R       , KC_T       , KC_Y       , KC_U       , KC_I       , KC_O       , KC_P       , KC_BSPC    ,
        TBLA       , KC_A       , KC_S       , KC_D       , KC_F       , KC_G       , KC_H       , KC_J       , KC_K       , KC_L       , KC_SCLN    , KC_QUOT    ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_N       , KC_M       , KC_COMM    , KC_DOT     , KC_SLSH    , SC_SENT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , LOWER      , KC_SPC     , KC_SPC     , RAISE      , KC_LEFT    , KC_DOWN    , KC_UP      , KC_RGHT
        ),
    [_COLEMAK] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_Q       , KC_W       , KC_F       , KC_P       , KC_G       , KC_J       , KC_L       , KC_U       , KC_Y       , KC_SCLN    , KC_BSPC    ,
        TBLA       , KC_A       , KC_R       , KC_S       , KC_T       , KC_D       , KC_H       , KC_N       , KC_E       , KC_I       , KC_O       , KC_QUOT    ,
        KC_LSFT    , KC_Z       , KC_X       , KC_C       , KC_V       , KC_B       , KC_K       , KC_M       , KC_COMMA   , KC_DOT     , KC_SLSH    , SC_SENT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , LOWER      , KC_SPC     , KC_SPC     , RAISE      , KC_LEFT    , KC_DOWN    , KC_UP      , KC_RGHT
        ),
    [_DVORAK] = LAYOUT_ortho_4x12(
        KC_ESC     , KC_QUOTE   , KC_COMMA   , KC_DOT     , KC_P       , KC_Y       , KC_F       , KC_G       , KC_C       , KC_R       , KC_L       , KC_BSPC    ,
        TBLA       , KC_A       , KC_O       , KC_E       , KC_U       , KC_I       , KC_D       , KC_H       , KC_T       , KC_N       , KC_S       , KC_SLSH    ,
        KC_LSFT    , KC_SCLN    , KC_Q       , KC_J       , KC_K       , KC_X       , KC_B       , KC_M       , KC_W       , KC_V       , KC_Z       , SC_SENT    ,
        KC_LCTL    , KC_LGUI    , KC_LALT    , KC_TAB     , LOWER      , KC_SPC     , KC_SPC     , RAISE      , KC_LEFT    , KC_DOWN    , KC_UP      , KC_RGHT
        ),
    [_SYMBLS] = LAYOUT_ortho_4x12(
        KC_MPLY    , KC_EXLM    , KC_AT      , KC_HASH    , KC_DLR     , KC_PERC    , KC_CIRC    , KC_AMPR    , KC_ASTR    , KC_LPRN    , KC_RPRN    , KC_BSPC    ,
        _____      , KC_F1      , KC_F2      , KC_F3      , KC_F4      , KC_F5      , KC_F6      , KC_UNDS    , KC_PLUS    , KC_LCBR    , KC_RCBR    , _____      ,
        _____      , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11     , KC_F12     , KC_PIPE    , KC_DQUO    , KC_TILD    , KC_QUES    , KC_MUTE    ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_MPRV    , KC_VOLD    , KC_VOLU    , KC_MNXT
    ),
    [_NUMBRS] = LAYOUT_ortho_4x12(
        KC_PSCR    , KC_1       , KC_2       , KC_3       , KC_4       , KC_5       , KC_6       , KC_7       , KC_8       , KC_9       , KC_0       , _____      ,
        _____      , _____      , KC_INS     , KC_HOME    , KC_PGUP    , _____      , _____      , KC_MINS    , KC_EQUAL   , KC_LBRC    , KC_RBRC    , _____      ,
        _____      , _____      , KC_DEL     , KC_END     , KC_PGDN    , _____      , _____      , KC_BSLS    , KC_QUOT    , KC_GRV     , KC_SLSH    , KC_MUTE    ,
        _____      , _____      , _____      , KC_MPLY    , _____      , _____      , _____      , _____      , KC_MPRV    , KC_VOLD    , KC_VOLU    , KC_MNXT
    ),
    [_ADJUST] = LAYOUT_ortho_4x12(
        _____      , UG_TOGG    , UG_HUEU    , UG_SATU    , UG_VALU    , _____      , _____      , _____      , _____      , _____      , _____      , DB_TOGG    ,
        _____      , UG_NEXT    , UG_HUED    , UG_SATD    , UG_VALD    , AG_NORM    , AG_SWAP    , QWRT       , DVRK       , CLMK       , _____      , _____      ,
        _____      , BL_TOGG    , BL_DOWN    , BL_UP      , BL_BRTG    , _____      , _____      , _____      , _____      , _____      , _____      , _____      ,
        QK_BOOT    , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____
    ),
    [_TABULA] = LAYOUT_ortho_4x12(
        C_A_D      , KC_ALTF4   , VK_TOGG    , _____      , _____      , _____      , KC_REDO    , _____      , _____      , _____      , _____      , _____      ,
        _____      , KC_SLCTALL , KC_SAVE    , _____      , KC_FIND    , _____      , _____      , _____      , KC_LCUT    , KC_LCOPY   , _____      , KC_KILL    ,
        _____      , KC_UNDO    , KC_CUT     , KC_COPY    , KC_PASTE   , KC_PRVWD   , KC_NXTWD   , TG(_MOUSY) , _____      , _____      , _____      , _____      ,
        _____      , _____      , _____      , _____      , NUMPAD     , KC_MPLY    , KC_MPLY    , _____      , KC_WBAK    , _____      , _____      , KC_WFWD
    ),
    [_NUMPAD] = LAYOUT_ortho_4x12(
        _____      , _____      , KC_INS     , KC_HOME    , KC_PGUP    , _____      , KC_PSLS    , KC_KP_7    , KC_KP_8    , KC_KP_9    , KC_PMNS    , _____      ,
        _____      , _____      , KC_DEL     , KC_END     , KC_PGDN    , _____      , KC_PAST    , KC_KP_4    , KC_KP_5    , KC_KP_6    , KC_PPLS    , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_KP_1    , KC_KP_2    , KC_KP_3    , KC_PAST    , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_KP_0    , KC_KP_0    , KC_PDOT    , KC_PENT    , _____
    ),
    [_MOUSY] = LAYOUT_ortho_4x12(
        _____      , _____      , _____      , KC_WH_U    , _____      , _____      , _____      , KC_BTN1    , KC_MS_U    , KC_BTN2    , _____      , _____      ,
        _____      , _____      , KC_WH_L    , KC_WH_D    , KC_WH_R    , _____      , _____      , KC_MS_L    , KC_MS_D    , KC_MS_R    , _____      , _____      ,
        _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_BTN3    , _____      , KC_UP      , _____      ,
        TO(_BASE)  , _____      , _____      , _____      , _____      , _____      , _____      , _____      , _____      , KC_LEFT    , KC_DOWN    , KC_RIGHT
    )
};

// Process Combo events
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case ZC_COPY:
            if (pressed) {
                tap_code16(LCTL(KC_C));
            }
            break;
        case XV_PASTE:
            if (pressed) {
                tap_code16(LCTL(KC_V));
            }
            break;
    }
}

// Runs every time a key is pressed or released
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case MO_SYMBLS:
            if (record->event.pressed) {
                layer_on(_SYMBLS);
            } else {
                layer_off(_SYMBLS);
            }
            return false;
        case MO_NUMBRS:
            if (record->event.pressed) {
                layer_on(_NUMBRS);
            } else {
                layer_off(_NUMBRS);
            }
            return false;
        case MO_FEATURS:
            if (record->event.pressed) {
                layer_on(_FEATURS);
            } else {
                layer_off(_FEATURS);
            }
            return false;
        case KC_PRVWD:  // Control+Left
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:  // Control+Right
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_PRVTAB:  // Control+Shift+Tab
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_TAB);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LSFT));
                unregister_code(KC_TAB);
            }
            break;
        case KC_NXTAB:  // Control+Tab
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_TAB);
                } else {
                    register_mods(mod_config(MOD_LSFT));
                    register_code(KC_TAB);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:  // Basically just Home
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:  // Basically just End
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    // CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:  // Control+BackSpace
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:  // Copy: Control+C
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:  // Paste: Control+V
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:  // Cut: Control+X
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:  // Undo: Control+Z
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case KC_REDO:  // Redo: Control+Y
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Y);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Y);
            }
            break;
        case KC_SAVE:  // Save: Control+S
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_S);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_S);
            }
            return false;
        case KC_FIND:  // Find: Control+F
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_F);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_F);
            }
            return false;
        case KC_SLCTALL:  // Select All: Control+A
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_A);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_A);
            }
            return false;
        case KC_KILL:  // Kill: Delete Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                tap_code(KC_DELETE);
            } else {
            }
            return false;
        case KC_LCUT:  // Cut Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                register_mods(mod_config(MOD_LCTL));
                tap_code(KC_X);
                unregister_mods(mod_config(MOD_LCTL));
            } else {
            }
            return false;
        case KC_LCOPY:  // Copy Line
            if (record->event.pressed) {
                tap_code(KC_HOME);
                register_mods(mod_config(MOD_LSFT));
                tap_code(KC_END);
                unregister_mods(mod_config(MOD_LSFT));
                register_mods(mod_config(MOD_LCTL));
                tap_code(KC_C);
                unregister_mods(mod_config(MOD_LCTL));
                tap_code(KC_END);
            } else {
            }
            return false;
        case KC_ALTF4:  // Close Window: Alt+F4
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LALT));
                register_code(KC_F4);
            } else {
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_F4);
            }
            return false;
        case ALT_TAB:  // Change Window: Super ⭍ Alt+Tab
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_BSPC: {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else {  // on release of KC_BSPC
                // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
        }
    }
    return true;
}

// Runs at every complete matrix scan
void matrix_scan_user(void) {
    // Monitor and respond to the current Alt+Tab state
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    // Run the wake-up RGB animation if performing wake-up
}

// EEPROM is getting reset!
void eeconfig_init_user(void) {
    user_config.raw                 = 0;
    eeconfig_update_user(user_config.raw);  // Write default value to EEPROM now
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYMBLS, _NUMBRS, _ADJUST);
}
