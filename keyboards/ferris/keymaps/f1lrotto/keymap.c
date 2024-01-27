#include QMK_KEYBOARD_H

static uint16_t key_timer;

enum layers {
    BASE = 0,
    MO1,
    MO2,
    MO3,
};

enum custom_keycodes {
    PRT_SNP, // Custom keycode for PrintScreen / Snip & Sketch
    DLR_EUR, // Custom keycode for Dollar / Euro
    ZM_IN,   // Custom keycode for Zoom In
    ZM_OUT,  // Custom keycode for Zoom Out
    ZM_IN_S, // Custom keycode for Zoom In (Shift)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PRT_SNP:
            if (record->event.pressed) {
                // Key was pressed
                key_timer = timer_read();
            } else {
                // Key was released
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    // Tapped: Send PrintScreen
                    tap_code(KC_PSCR);
                } else {
                    // Held: Send Windows Snip & Sketch (Win + Shift + S)
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    tap_code(KC_S);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_LGUI);
                }
            }
            break;
        case DLR_EUR:
            if (record->event.pressed) {
                // Key was pressed
                key_timer = timer_read();
            } else {
                // Key was released
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    // Tapped: Send Dollar
                    SEND_STRING("$");
                } else {
                    // Held: Send Euro
                    send_unicode_string("€");
                }
            }
            break;
        case ZM_IN:
            if (record->event.pressed) {
                // When ZOOM_IN key is pressed
                register_code(KC_LCTL);
                tap_code(KC_EQUAL); // Ctrl + Plus
                unregister_code(KC_LCTL);
            }
            break;

        case ZM_OUT:
            if (record->event.pressed) {
                // When ZOOM_OUT key is pressed
                register_code(KC_LCTL);
                tap_code(KC_MINUS); // Ctrl + Minus
                unregister_code(KC_LCTL);
            }
            break;
        case ZM_IN_S:
            if (record->event.pressed) {
                // When ZOOM_IN_SHIFT key is pressed
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_EQL); // Ctrl + Shift + Equals (Plus)
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;
    }
    return true;
};

// Custom Keycodes base layer
#define KC_MZ LALT_T(KC_Z)
#define KC_MSLSH LALT_T(KC_SLSH)
#define KC_MA LCTL_T(KC_A)
#define KC_MQUOT LCTL_T(KC_QUOT)

// Custom Keycodes base layer thumb
#define TC_1 LT(MO1, KC_BSPC)
#define TC_2 LT(MO2, KC_SPC)
#define TC_3 LT(MO3, KC_ENT)

// Custom Keycodes MO1 layer
#define MS_W_UP KC_MS_WH_UP
#define MS_W_DN KC_MS_WH_DOWN




// Combo keys
const uint16_t PROGMEM c_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM c_lcmd[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM c_rcmd[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM c_bsp[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM c_del[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM c_tab[] = {KC_D, KC_F, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    COMBO(c_esc, KC_ESC),
    COMBO(c_lcmd, KC_LGUI),
    COMBO(c_rcmd, KC_LGUI),
    COMBO(c_bsp, KC_BSPC),
    COMBO(c_del, KC_DEL),
    COMBO(c_tab, KC_TAB),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_MA,   KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_MQUOT,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_MZ,   KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_MSLSH,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                       TC_1,    KC_LSFT,    TC_2,    TC_3),

    [MO1] = LAYOUT(
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            _______, MS_W_DN, KC_UP,   MS_W_UP, DT_UP,      ZM_OUT,  ZM_IN,   ZM_IN_S, _______, _______,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, DT_PRNT,    KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            PRT_SNP, KC_PGDN, _______, KC_PGUP, DT_DOWN,    _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                       _______, _______,    KC_LSFT, KC_LCTL),

    [MO2] = LAYOUT(
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_F11,  KC_F12,  _______, _______, _______,    KC_EQL,  KC_PLUS, KC_ASTR, KC_MINS, KC_SLSH,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                       _______, _______,    _______,  KC_PERC),

    [MO3] = LAYOUT(
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE, _______,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_GRV,  KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC,    KC_COLN, KC_SCLN, _______, _______, _______,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
            KC_TILD, KC_RABK, KC_RCBR, KC_RPRN, KC_RBRC,    KC_EQL,  KC_PLUS, KC_UNDS, KC_MINS, KC_BSLS,
        // |--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                       _______, _______,    _______, _______),
};
