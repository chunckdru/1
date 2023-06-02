#ifndef __WS2812_H__
#define __WS2812_H__
#include "main.h"
#include "keymap.h"
#include "key_matrix.h"
void ws2812_animation_rainbow(void);
void ws2812_animation_breathing(void);
void ws2812_animation_start(void);
void ws2812_init(void);
extern uint8_t rgb_mode;
#endif
