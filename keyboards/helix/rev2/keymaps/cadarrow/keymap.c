#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    EISU,
    KANA,
    RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)
#if !defined( REVERSED_COL_PINS_KEYMAP )
#pragma error "REVERSED_COL_PINS_KEYMAP should be yes in rules.mk"
#endif

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   *        ,-----------------------------------------------------------------------------------.
   *        |      |      |      |      |      |      |  DEL | ESC  |  F4  |      | Home | DEL  |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        |      |      |      |      |      |      |  ALT |  S   |  R   |  Y   | End  | BS   |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        |      |      |      |      |      |      |  Z   |  X   |  C   |  V   | PgUP | ENT  |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Gui  |Shift |      |  UP  | PgDN | SH   | LOWER|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Ctl  |Shift | Left | Down | Right| RCTL | ADJ  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
               KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_DEL , KC_ESC , KC_F4  , KC_NO  , KC_HOME, KC_DEL , \
               KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_LALT, KC_NO  , KC_S   , KC_Y   , KC_END , KC_BSPC, \
               KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_Z   , KC_X   , KC_C   , KC_V   , KC_PGUP, KC_ENT , \
      KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_LGUI, KC_LSFT, KC_NO  , KC_UP  , KC_PGDN, KC_RSFT, LOWER, \
      KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_LCTL, KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_RCTL, ADJUST   \
      ),

  /* Lower
   *        ,-----------------------------------------------------------------------------------.
   *        | `~   |      |      |   '  |   "  |   /  |  (@) |   *  |   -  |   =  |  \|  | DEL  |
   *        |------+------+------+------+------+------+------+------+------+------+------+------|
   *        |  (!) |  (") |  (#) |  ($) |  (%) |  (^) |  (&) |   {  |   }  |   [  |   ]  | \|   |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  (@) |  `   |  (*) |   \  |  (|) |  (|) |   ;  |  (:) |  (() |  ()) | ENT  |
   * |------|------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  (^) |  (~) |  (_) |  -   |  +   |  (_) |  ,<  |  .>  |  /?  | (¥_) | SH   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |  SPC |  SPC |      | ALT  | GUI  | APP  | CTL  |      |
   * `-------------------------------------------------------------------------------------------------'
   * (char) has language dependency.
   */
  [_LOWER] = LAYOUT( \
             KC_GRV , KC_NO  , KC_NO  , KC_QUOT, KC_DQT , KC_PSLS,   KC_AT  , KC_ASTR, KC_MINS, KC_EQL , KC_INT3, KC_DEL , \
             KC_EXLM, KC_DQT , KC_HASH, KC_DLR , KC_PERC, KC_CIRC,   KC_AMPR, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS, \
             _______, KC_AT  , KC_GRV , KC_ASTR, KC_BSLS, KC_PIPE,   KC_PIPE, KC_SCLN, KC_COLN, KC_LPRN, KC_RPRN, _______, \
    _______, _______, KC_CIRC, KC_TILD, KC_UNDS, KC_PMNS, KC_PPLS,   KC_UNDS, KC_COMM, KC_DOT , KC_SLSH, KC_INT1, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,   KC_SPC , KC_NO  , KC_RALT, KC_RGUI, KC_APP , _______, _______  \
    ),

  /* Raise
   *        ,-----------------------------------------------------------------------------------.
   *        |  `~  |      |      |      |      |      | ESC  | PSc  | Ins  | Home | PgU  | DEL  |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F1  |  F2  |  F3  |  45  |  F5  |      |      | DEL  | End  | PgD  |      |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |      | PgU  | UP   | PgD  | ENT  |     
   * |------|------+------+------+------+------+------+------+------+------+------+------+------|------|
   * |      |      |  F11 |  F12 |      |      |      |      |      | LEFT | DOWN | RIGHT| SH   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |  SPC | SPC  |      |      |      |      | CTL  |      |
   * `--------------------------------------------------------------------------------------------------' 
   * definition is reversed.
   */
  [_RAISE] = LAYOUT( \
             KC_GRV , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_ESC , KC_PSCR, KC_INS , KC_HOME, KC_PGUP, KC_DEL , \
             _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,   KC_NO  , KC_NO  , KC_DEL , KC_END , KC_PGDN, _______, \
             _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,   KC_NO  , KC_NO  , KC_PGUP, KC_UP  , KC_PGDN, _______, \
    _______, _______, KC_F11 , KC_F12 , KC_NO  , KC_NO  , KC_NO  ,   KC_NO  , KC_NO  , KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,\
    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Adjust (Lower + Raise)
   *        ,-----------------------------------------------------------------------------------.
   *        |      |      |      |      |      |      |Reset |RGBRST|      |      |      |      |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |             |      |      |      |RGB ON|RGBMOD|Aud on|Audoff|      |      |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |                                  |      |      | SAT- | VAL+ | SAT+ |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      | HUE- | VAL- | HUE+ |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
               _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   RESET  , RGBRST , KC_NO  , KC_NO  , KC_NO  , _______, \
               _______, RESET  , RGBRST , KC_NO  , KC_NO  , KC_NO  ,   RGB_TOG, RGB_MOD , AU_ON  , AU_OFF , KC_NO  , _______, \
               _______, RGB_TOG, RGB_MOD, AU_ON  , AU_OFF , KC_NO  ,   KC_NO  , KC_NO  , RGB_SAD, RGB_VAI, RGB_SAI, _______, \
      _______, _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,   KC_NO  , KC_NO  , RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______  \
      )
};

#elif MATRIX_ROWS == 8 // HELIX_ROWS == 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   *        ,-----------------------------------------------------------------------------------.
   *        | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
              KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R,  KC_T,     KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC, \
              KC_LCTL, KC_A,    KC_S,    KC_D, KC_F,  KC_G,     KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
              KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V,  KC_B,     KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      ADJUST, KC_ESC,  KC_LALT, KC_LGUI, EISU, LOWER, KC_SPC,   KC_SPC, RAISE,  KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Lower
   *        ,-----------------------------------------------------------------------------------.
   *        |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
               KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
               _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5  ,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
               _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 ,   KC_F12,  _______, _______, KC_HOME, KC_END,  _______, \
      _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   *        ,-----------------------------------------------------------------------------------.
   *        |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
               KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5   ,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
               _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5  ,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
               _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 ,   KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______, \
      _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Adjust (Lower + Raise)
   *        ,-----------------------------------------------------------------------------------.
   *        |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |      |      |Aud on|Audoff| Mac  | Win  |Qwerty|Colemk|Dvorak|      |      |
   *        |------+------+------+------+------+------|------+------+------+------+------+------|
   *        |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
               _______, RESET,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_DEL, \
               _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,   AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
               _______, _______, _______, _______, _______, _______,   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}


static  long unsigned int  logo_state = 0;
#define  LOGO_STATE_TMO   10000

static void render_logo(struct CharacterMatrix *matrix)
 {
    static char logo[]={
#if defined(USE_SLAVE_FONT)
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,
#endif
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};

    if (  0 == (logo_state % LOGO_STATE_TMO ) )
    {
        matrix_clear(matrix);
        matrix_write(matrix, logo);
        logo_state++;
    }
}



//assign the right code to your layers for OLED display
#define L_BASE       0
#define L_LOWER      (1<<_LOWER)
#define L_RAISE      (1<<_RAISE)
#define L_ADJUST     (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)
#define L_UNDEF      (-1)


static long int  old_layer_state = L_UNDEF;

void render_status(struct CharacterMatrix *matrix)
{
    char buf[40];

    if (old_layer_state == layer_state)
        return;

    matrix_clear(matrix);
    snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
    switch (layer_state) {
    case L_BASE:
        matrix_write_P(matrix, PSTR(" CTL + ALT + DEL"));
        break;
    case L_RAISE:
        matrix_write_P(matrix, PSTR("  R A I S E  "));
        break;
    case L_LOWER:
        matrix_write_P(matrix, PSTR("      ' / * @ - = \\\n"));
        matrix_write_P(matrix, PSTR("! \" # $ % & { } [ ]\n"));
        matrix_write_P(matrix, PSTR("@ ` * \\ | ; : \" ( )\n"));
        matrix_write_P(matrix, PSTR("^ ~ _ - + _ , . /"));
        break;
    case L_ADJUST:
    case L_ADJUST_TRI:
    {
        char l2[] = { 0x20,0x20, 0x80,0x20, 0x81,0x20, '\n', 0x00 };
        char l3[] = { 0x20,0x20, 0x83,0x20, 0x84,0x20, 0x85,0x86, 0x20,0x20, 0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,'\n', 0x00 };
        char l4[] = { 0x20,0x20, 0x20,0x20, 0x20,0x20, 0x20,0x20, 0x20,0x20, 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7, 0x00 };
 
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write(matrix, l2);
        matrix_write(matrix, l3);
        matrix_write(matrix, l4);
        break;
    }
    default:
        matrix_write(matrix, buf);
    }
    old_layer_state = layer_state;
}


void iota_gfx_task_user(void)
{
    struct CharacterMatrix *p_matrix = matrix_getInstance();

#if DEBUG_TO_SCREEN
    if (debug_enable) {
      return;
    }
#endif

#if defined(USE_SLAVE_FONT)
    matrix_set_page_mode(!is_master);
    matrix_set_font_no(is_master ? 0 : 1);
#endif
    if (is_master) {  render_status(p_matrix);  }
    else           {  render_logo(p_matrix);    }
}

