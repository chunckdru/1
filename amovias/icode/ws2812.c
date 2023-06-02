#include "ws2812.h"
#include "tim.h"
#define ONE_PULSE        		59  //1码计数个数
#define ZERO_PULSE       		29  //0码计数个数
#define RESET_PULSE      		80  //复位电平个数
#define LED_DATA_LEN     		24  //led数据长度
#define WS2812_DATA_LEN   	(LED_NUMS*LED_DATA_LEN)  //总灯条所需数据长度
#define MAX_BRIGHTNESS   		255	//led最大亮度
#define BRIGHTNESS          ((uint8_t)(MAX_BRIGHTNESS*BRIGHTNESS_RATIO)/6*6) //实际亮度
#define OFFSET              (uint8_t)(led_pos[j][1]*THICKNESS*BRIGHTNESS_RATIO+i)

uint8_t brightness = BRIGHTNESS;
uint8_t animation_speed = ANIMATION_SPEED*5;
uint16_t static RGB_buffer[RESET_PULSE+WS2812_DATA_LEN] = { 0 };
uint16_t static rainbow_palette[BRIGHTNESS][3] = { 0 };
uint16_t static breathing_palette[2*BRIGHTNESS][3] = { 0 };
uint16_t static total_brightness[BRIGHTNESS] = { 0 };
uint16_t static total_brightness1[2*BRIGHTNESS] = { 0 };
uint8_t rgb_mode = 0;

void brightness_init1(void)
{
	uint8_t max = brightness/6;
	
	for(uint8_t i = 0;i < brightness;i++)
	{
		total_brightness1[i] = 0;
	}
	
	for(uint8_t i = 0;i < max+1;i++)
	{
		total_brightness1[i] = total_brightness1[i-1]+6;
		total_brightness1[i+2*max] = total_brightness1[i+2*max-1]+6;
		total_brightness1[i+4*max] = total_brightness1[i+4*max-1]+6;
		total_brightness1[i+6*max] = total_brightness1[i+6*max-1]+6;
		total_brightness1[i+8*max] = total_brightness1[i+8*max-1]+6;
		total_brightness1[i+10*max] = total_brightness1[i+10*max-1]+6;
	}
	
	for(uint8_t i = 0;i < 2*max+1;i++)
	{
		total_brightness1[i] = total_brightness1[i-1]+6;
		total_brightness1[i+2*max] = total_brightness1[i+2*max-1]+6;
		total_brightness1[i+4*max] = total_brightness1[i+4*max-1]+6;
		total_brightness1[i+6*max] = total_brightness1[i+6*max-1]+6;
		total_brightness1[i+8*max] = total_brightness1[i+8*max-1]+6;
	}
	
	for(uint8_t i = 0;i < 2*max;i++)
	{
		total_brightness1[i+10*max] = total_brightness1[i+10*max-1]+6;
	}
}

void palette_init1(void)
{
	uint16_t size = 2*brightness;
	uint16_t (*p)[3] = breathing_palette;
	for(uint16_t i = 0;i < 3;i++)
	{
		for(uint16_t j = 0;j < size;j++)
		{
			switch(i)
			{
				case 0://R
					if((j > size/6 && j < size/3) || (j > size/2 && j < 2*size/3))
						p[j][i] = total_brightness1[j]/2;
					else if((j > size/3 && j < size/2))
						p[j][i] = total_brightness1[j];
					else
						p[j][i] = 0;
					break;
				case 1://G
					if((j > size/6 && j < size/3) || (j > 5*size/6))
						p[j][i] = total_brightness1[j]/2;
					else if(j < size/6)
						p[j][i] = total_brightness1[j];
					else
						p[j][i] = 0;
					break;
				case 2://B
					if((j > size/2 && j < 2*size/3) || (j > 5*size/6))
						p[j][i] = total_brightness1[j]/2;
					else if(j > 2*size/3 && j < 5*size/6)
						p[j][i] = total_brightness1[j];
					else
						p[j][i] = 0;
					break;
			}
		}
	}
}

void brightness_init(void)
{
	uint8_t max = brightness/6;
	
	for(uint8_t i = 0;i < brightness;i++)
	{
		total_brightness[i] = brightness;
	}
	
	for(uint8_t i = 0;i < max+1;i++)
	{
		total_brightness[i] = total_brightness[i-1]+6;
		total_brightness[i+2*max] = total_brightness[i+2*max-1]+6;
		total_brightness[i+4*max] = total_brightness[i+4*max-1]+6;
	}
	
	for(uint8_t i = 0;i < 2*max+1;i++)
	{
		total_brightness[i] = total_brightness[i-1]+6;
		total_brightness[i+2*max] = total_brightness[i+2*max-1]+6;
	}
	
	for(uint8_t i = 0;i < 2*max;i++)
	{
		total_brightness[i+4*max] = total_brightness[i+4*max-1]+6;
	}
}

void palette_init(void)
{
	uint16_t (*p)[3] = rainbow_palette;
	
	for(uint16_t i = 0;i < 3;i++)
	{
		for(uint16_t j = 0;j < brightness;j++)
		{
			switch(i)
			{
				case 0://R
					if(j >= brightness/6 && j < brightness/2)
						p[j][i] = brightness;
					else if(j >= 2*brightness/3)
						p[j][i] = 0;
					break;
				case 1://G
					if(j < brightness/6 || j > 5*brightness/6)
						p[j][i] = brightness;
					else if(j > brightness/3 && j <= 2*brightness/3)
						p[j][i] = 0;
					break;
				case 2://B
					if(j > brightness/2 && j > 5*brightness/6)
						p[j][i] = brightness;
					else if(j < brightness/3)
						p[j][i] = 0;
					break;
			}
		}
	}
	
	for(uint16_t i = 0;i < 3;i++)
	{
		for(uint16_t j = 0;j < brightness;j++)
		{
			switch(i)
			{
				case 0://R
					if(j < brightness/6 || (j > brightness/2 && j < 2*brightness/3))
						p[j][i] = total_brightness[j]-p[j][i+1]-p[j][i+2];
					break;
				case 1://G
					if((j > brightness/6 && j < brightness/3)|| (j > 2*brightness/3 && j < 5*brightness/6))
						p[j][i] = total_brightness[j]-p[j][i-1]-p[j][i+1];
					break;
				case 2://B
					if((j > brightness/3 && j < brightness/2) || j > 5*brightness/6)
						p[j][i] = total_brightness[j]-p[j][i-1]-p[j][i-2];
					break;
			}
		}
	}
}

void ws2812_init(void)
{
	brightness_init();
	brightness_init1();
	palette_init();
	palette_init1();
}

void ws2812_set_RGB(uint8_t R, uint8_t G, uint8_t B, uint8_t num)
{
	uint16_t* p = (RGB_buffer + RESET_PULSE) + (num * LED_DATA_LEN);
	
	for(uint16_t i = 0;i < 8;i++)
	{
		p[i] = (G << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
		p[i+8] = (R << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
		p[i+16] = (B << i) & (0x80) ? ONE_PULSE : ZERO_PULSE;
	}
}

void ws2812_animation_rainbow(void)
{
	uint8_t s = 0;
	
	for(uint8_t i = 0;i < brightness;i++)
	{
		for(uint8_t j = 0;j < LED_NUMS;j++)
		{
			ws2812_set_RGB(rainbow_palette[(OFFSET)%brightness][1],rainbow_palette[(OFFSET)%brightness][0],rainbow_palette[(OFFSET)%brightness][2],j);
		}
		
		HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t*)RGB_buffer,(RESET_PULSE + WS2812_DATA_LEN));
		
		while(animation_speed--)
		{
			key_scan();
			if(rgb_mode == 1)
			{
				s = 1;
				break;
			}
		}
		
		if(s == 1)
			break;
	}
}

void ws2812_animation_breathing(void)
{
	uint8_t s = 1;
	
	for(uint16_t i = 0;i < 2*brightness;i++)
	{
		if(rgb_mode == 0)
			break;
		for(uint8_t j = 0;j < LED_NUMS;j++)
		{
			ws2812_set_RGB(breathing_palette[i][1],breathing_palette[i][0],breathing_palette[i][2],j);
		}
		
		HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t*)RGB_buffer,(RESET_PULSE + WS2812_DATA_LEN));
		
		while(4*animation_speed--)
		{
			key_scan();
			if(rgb_mode == 0)
			{
				s = 0;
				break;
			}
		}
		
		if(s == 0)
			break;
	}
}

void ws2812_animation_start(void)
{
	switch(rgb_mode)
	{
		case 0:
			ws2812_animation_rainbow();break;
		case 1:
			ws2812_animation_breathing();break;
		default:break;
	}
}



