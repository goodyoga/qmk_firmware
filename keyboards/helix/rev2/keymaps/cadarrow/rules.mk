# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#
LINK_TIME_OPTIMIZATION_ENABLE = no  # if firmware size over limit, try this option

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

# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))