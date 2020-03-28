# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no

LAYOUTS = 60_hhkb

# Features I added
TAP_DANCE_ENABLE = yes