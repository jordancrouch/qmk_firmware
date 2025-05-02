#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_uk.h"

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };
enum custom_keycodes { GRAVE_TILDE = SAFE_RANGE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MPLY, KC_MPLY, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_NUHS), KC_LALT, KC_LGUI, TG(1), KC_SPC, KC_ENT, TG(2), KC_BSPC, KC_DEL),
                                                              [1] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F12, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NUHS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_PMNS, KC_PLUS, KC_LCBR, KC_RCBR, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT(KC_TRNS, KC_NO, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_HOME, KC_TRNS, KC_HASH, KC_P4, KC_P5, KC_P6, KC_PAST, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_END, KC_TRNS, KC_AMPR, KC_P1, KC_P2, KC_P3, KC_PPLS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_PGUP, KC_TRNS, KC_DLR, KC_P0, KC_PDOT, KC_PEQL, KC_PMNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT(QK_BOOT, KC_NO, KC_NO, KC_NO, NK_TOGG, AC_TOGG, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, UG_NEXT, UG_SATU, UG_TOGG, QK_RBT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UG_PREV, UG_SATD, KC_NO, AS_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_CAPS, KC_NO, KC_NO, KC_NO, UG_HUEU, UG_VALU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UG_HUED, UG_VALD, EE_CLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

// Override the ESCAPE_GRAVE key to send the UK_TILD key when pressed with Shift
bool process_grave_esc_override_user(uint16_t *keycode, keyrecord_t *record) {
    if (get_mods() & MOD_MASK_SHIFT) {
        *keycode = UK_TILD; // Send tilde when shift is held
    }
    return true;
}

// RGB Light Layers
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 70, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 70, HSV_CYAN});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 70, HSV_RED});

// Define the array of RGB light layers
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_layer1_layer, my_layer2_layer, my_layer3_layer);

// Enables the RGB light layers
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;

#ifdef AUTO_SHIFT_ENABLE
    autoshift_disable();
#endif
}

// Layer state handling
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
    return state;
}

// Encoder handling
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {[0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [1] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}, [2] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}, [3] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}};
#endif

// OLED handling
#ifdef OLED_ENABLE
static void print_status_narrow(void) {
    // Create OLED content
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("M&J   -<3-"), false);
    oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case 3:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);

#    ifdef AUTO_SHIFT_ENABLE

    bool autoshift = get_autoshift_state();
    oled_advance_page(true);
    oled_write_P(PSTR("Auto-Shift"), autoshift);
    oled_advance_page(true);

#    endif
}

bool oled_task_user(void) {
    // Render the OLED
    print_status_narrow();
    return false;
}

#endif