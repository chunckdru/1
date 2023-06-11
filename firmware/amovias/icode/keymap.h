#ifndef __KEYMAP_H__
#define __KEYMAP_H__
#include "main.h"
#include "config.h"
#define KC_NO 0x00
#define KC_GRV 0x35
#define KC_1 0x1E
#define KC_2 0x1F
#define KC_3 0x20
#define KC_4 0x21
#define KC_5 0x22
#define KC_6 0x23
#define KC_7 0x24
#define KC_8 0x25
#define KC_9 0x26
#define KC_0 0x27
#define KC_MINS 0x2D
#define KC_EQL 0x2E
#define KC_BSPC 0x2A
#define KC_TAB 0x2B
#define KC_Q 0x14
#define KC_W 0x1A
#define KC_E 0x08
#define KC_R 0x15
#define KC_T 0x17
#define KC_Y 0x1C
#define KC_U 0x18
#define KC_I 0x0C
#define KC_O 0x12
#define KC_P 0x13
#define KC_LBRC 0x2F
#define KC_RBRC 0x30
#define KC_BSLS 0x31
#define KC_CAPS 0x39
#define KC_A 0x04
#define KC_S 0x16
#define KC_D 0x07
#define KC_F 0x09
#define KC_G 0x0A
#define KC_H 0x0B
#define KC_J 0x0D
#define KC_K 0x0E
#define KC_L 0x0F
#define KC_SCLN 0x33
#define KC_QUOT 0x34
#define KC_ENT 0x28
#define KC_LSFT 0xE1
#define KC_Z 0x1D
#define KC_X 0x1B
#define KC_C 0x06
#define KC_V 0x19
#define KC_B 0x05
#define KC_N 0x11
#define KC_M 0x10
#define KC_COMM 0x36
#define KC_DOT 0x37
#define KC_SLSH 0x38
#define KC_RSFT 0xE5
#define KC_LCTL 0xE0
#define KC_LGUI 0xE3
#define KC_LALT 0xE2
#define KC_SPC 0x2C
#define KC_RALT 0xE6
#define KC_RGUI 0xE7
#define KC_RCTL 0xE4
#define KC_F1 0x3A
#define KC_F2 0x3B
#define KC_F3 0x3C
#define KC_F4 0x3D
#define KC_F5 0x3E
#define KC_F6 0x3F
#define KC_F7 0x40
#define KC_F8 0x41
#define KC_F9 0x42
#define KC_F10 0x43
#define KC_F11 0x44
#define KC_F12 0x45
#define MO(layer) (0xE8 + layer)
#define RGB_MODE 0xff
extern uint8_t led_pos[LED_NUMS][2];
extern uint8_t keymap[][KEY_ROW_NUM][KEY_COL_NUM];
#endif