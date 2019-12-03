# The Default Helix Layout
## Layout

### Qwerty

```
        ,-----------------------------------------------------------------------------------.
        | ZKHK |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | ENT  |
 |------|------+------+------+------+------+------+------+------+------+------+------+------------|
 |RAISE | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | SFT  |LOWER |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| CTL  | Alt  | GUI  |      |Lower |Space |Space |Raise | ALT  | GUI  | APP  | CTL  |Right |
 `-------------------------------------------------------------------------------------------------'
```

## Layers

|Priority|number|name|description|
| ---- | ---- | --- | --- |
|high|16|Adjust|Functions|
||4|Raise|Numeric charactors|
||3|Lower|Other charactors|
|low|0|Qwerty|QWERTY leyout(base)|

### Lower
```
        ,-----------------------------------------------------------------------------------.
        | `~   |      |      |      |   '  |   /  |   *  |   @  |   -  |   =  |  \|  | DEL  |
        |------+------+------+------+------+------+------+------+------+------+------+------|
        | TAB  |  !   |  "   |  #   |  $   |  %   |   &  |   {  |  }   |   [  |   ]  | \|   |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        |      |  @   |  `   |  *   |  \   |   |  |   ;  |  :   |  "   |   (  |   )  | ENT  |
 |------|------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |  ^   |  ~   |  _   |  -   |  +   |   _  | ,<   |  .>  | /?   |  ¥_  | SH   |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |  SPC |  SPC |      |      |      |      | CTL  |      |
 `-------------------------------------------------------------------------------------------------'
```

### Raise
```
        ,-----------------------------------------------------------------------------------.
        |  ZH  |      |      |      |      |      | ESC  | Ins  | Home | PgU  | PSc  | BS   |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        |      |  F1  |  F2  |  F3  |  45  |  F5  |      | DEL  | End  | PgD  |      |      |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |      | UP   |      |      | ENT  |     
 |------|------+------+------+------+------+------+------+------+------+------+------+------|------|
 |      |      |  F11 |  F12 |      |      |      |      | LEFT | DOWN | RIGHT|      | SH   |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |  SPC | SPC  |      |      |      |      | CTL  |      |
 `--------------------------------------------------------------------------------------------------' 
```

### Adjust (Lower + Raise)
```
        ,-----------------------------------------------------------------------------------.
        |      |      |      |      |      |      |      |      |      |      |      |      |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        |      | Reset|RGBRST|      |      |      |      |      |      |      |      |  Del |
        |------+------+------+------+------+------|------+------+------+------+------+------|
        |      |RGB ON|RGBMOD|Aud on|Audoff|      |      | SAT- | VAL+ | SAT+ |      |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      | HUE- | VAL- | HUE+ |      |      |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 `-------------------------------------------------------------------------------------------------'
```

## Customize

see `qmk_firmware/keyboards/helix/rev2/keymaps/reversed/rules.mk`

```
# Helix Spacific Build Options
# you can uncomment and edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集し、コメントアウトをはずします。
HELIX_ROWS        = 5       # Helix Rows is 4 or 5
OLED_ENABLE       = yes     # OLED_ENABLE
LOCAL_GLCDFONT    = yes     # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# FONT_SIZE_LARGE = yes     # needs LOCAL_GLCDFONT, still buggy. 
USE_SLAVE_FONT    = yes     # use another font for slave.
LED_BACK_ENABLE   = yes     # LED backlight (Enable WS2812 RGB underlight.)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS    = yes     # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
REVERSED_COL_PINS_KEYMAP = yes   # Left is right side, Right is left side
```

### USE_SLAVE_FONT

See readme_jp.md for more details.

### REVERSED_COL_PINS_KEYMAP

See readme_jp.md for more details.



## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make helix:reversed
```

flash to keyboard
```
$ make helix:reversed:avrdude

```

## Link
* more detail wrote in Japanese [helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)
* [Helix top](https://github.com/MakotoKurauchi/helix)

