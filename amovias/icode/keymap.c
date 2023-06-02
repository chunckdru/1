#include "keymap.h"

uint8_t keymap[][KEY_ROW_NUM][KEY_COL_NUM]=
{
	[0] = {
		KC_GRV, 	KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,	KC_8,		KC_9,		KC_0,		KC_MINS,	KC_EQL,	KC_BSPC,
		KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,	KC_I,		KC_O,		KC_P,		KC_LBRC,	KC_RBRC,KC_BSLS,
		KC_CAPS,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,	KC_K,		KC_L,		KC_SCLN,KC_QUOT,	KC_ENT,	KC_NO,
		KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,	KC_COMM,KC_DOT,	KC_SLSH,KC_RSFT,	KC_NO,	KC_NO,
		KC_LCTL,	KC_LGUI,KC_LALT,KC_NO,	KC_NO,	KC_SPC,	KC_NO,	KC_NO,KC_RALT,KC_RGUI,MO(1),	KC_RCTL,	KC_NO,	KC_NO
	},
	[1] = {
		KC_NO, 	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_F11,	KC_F12,	RGB_MODE,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
	},
};
uint8_t led_pos[LED_NUMS][2] ={
	{0,0},	{0,18},	{0,37},	{0,55},		{0,74},		{0,92},		{0,110},	{0,129},	{0,147},	{0,165},	{0,184},	{0,202},	{0,241},{0,248},
	{18,5},	{18,28},{18,41},{18,60},	{18,78},	{18,96},	{18,115},	{18,133},	{18,152},	{18,170},	{18,188},	{18,207},	{18,225},	{18,248},
	{37,7},	{37,32},{37,51},{37,69},	{37,87},	{37,106},	{37,124},	{37,142},	{37,161},	{37,179},	{37,198},	{37,216},	{37,246},
	{74,11},{74,41},{74,60},{74,78},	{74,96},	{74,115},	{74,133},	{74,152},	{74,170},	{74,188},	{74,207},	{74,241},
	{92,2},	{92,25},									{92,48},											{92,117},	{92,186},	{92,209},	{92,232},	{92,255}
};

