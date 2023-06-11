#include"key_matrix.h"

uint8_t buffer[8] = {0};
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t row_read(void)
{
	uint8_t row=0x00;
	row |= HAL_GPIO_ReadPin(ROW0_GPIO_Port,ROW0_Pin);
	row |= HAL_GPIO_ReadPin(ROW1_GPIO_Port,ROW1_Pin)<<1;
	row |= HAL_GPIO_ReadPin(ROW2_GPIO_Port,ROW2_Pin)<<2;
	row |= HAL_GPIO_ReadPin(ROW3_GPIO_Port,ROW3_Pin)<<3;
	row |= HAL_GPIO_ReadPin(ROW4_GPIO_Port,ROW4_Pin)<<4;
	return row;
}

void col_write(uint16_t col)
{
	HAL_GPIO_WritePin(COL0_GPIO_Port,COL0_Pin,col&0x01);
	HAL_GPIO_WritePin(COL1_GPIO_Port,COL1_Pin,col>>1&0x01);
	HAL_GPIO_WritePin(COL2_GPIO_Port,COL2_Pin,col>>2&0x01);
	HAL_GPIO_WritePin(COL3_GPIO_Port,COL3_Pin,col>>3&0x01);
	HAL_GPIO_WritePin(COL4_GPIO_Port,COL4_Pin,col>>4&0x01);
	HAL_GPIO_WritePin(COL5_GPIO_Port,COL5_Pin,col>>5&0x01);
	HAL_GPIO_WritePin(COL6_GPIO_Port,COL6_Pin,col>>6&0x01);
	HAL_GPIO_WritePin(COL7_GPIO_Port,COL7_Pin,col>>7&0x01);
	HAL_GPIO_WritePin(COL8_GPIO_Port,COL8_Pin,col>>8&0x01);
	HAL_GPIO_WritePin(COL9_GPIO_Port,COL9_Pin,col>>9&0x01);
	HAL_GPIO_WritePin(COL10_GPIO_Port,COL10_Pin,col>>10&0x01);
	HAL_GPIO_WritePin(COL11_GPIO_Port,COL11_Pin,col>>11&0x01);
	HAL_GPIO_WritePin(COL12_GPIO_Port,COL12_Pin,col>>12&0x01);
	HAL_GPIO_WritePin(COL13_GPIO_Port,COL13_Pin,col>>13&0x01);
}

void key_scan(void)
{
	uint8_t row[14] = {0};
	uint8_t layer=0;
	uint8_t n=2;
	uint8_t bit0=0;
	
	for(uint8_t i = 0;i < 14;i++)
	{
		col_write(0x01 << i);
		row[i]=row_read();
	}
	
	for(uint8_t i = 0;i < KEY_COL_NUM;i++)
	{
		for(uint8_t j = 0;j < KEY_ROW_NUM;j++)
		{
			if((row[i] >> j&0x01) == 1 && keymap[layer][j][i] >= 0xe8 && keymap[layer][j][i] <= 0xff)
			{
				layer += keymap[layer][j][i] - 0xe8;
				break;
			}
		}
	}
	
	for(uint8_t i = 0;i < KEY_COL_NUM;i++)
	{
		for(uint8_t j = 0;j < KEY_ROW_NUM;j++)
		{
			if((row[i] >> j&0x01) == 1 && keymap[layer][j][i] == 0xff)
			{
				HAL_Delay(500);
				rgb_mode = 1 - rgb_mode;
				break;
			}
		}
	}
	
	for(uint8_t i = 0;i < KEY_COL_NUM;i++)
	{
		for(uint8_t j = 0;j < KEY_ROW_NUM;j++)
		{
			if((row[i] >> j&0x01) == 1)
			{
				buffer[n++] = keymap[layer][j][i];

			}
			else
			{
				buffer[n]=KC_NO;
			}
		}
	}
	
	for(uint8_t i = 2;i < 8;i++)
	{
		switch(buffer[i])
		{
			case KC_LCTL: bit0 |= 0x01<<0;break; 
			case KC_LSFT: bit0 |= 0x01<<1;break;
			case KC_LALT: bit0 |= 0x01<<2;break;
			case KC_LGUI: bit0 |= 0x01<<3;break;
			case KC_RCTL: bit0 |= 0x01<<4;break;
			case KC_RSFT: bit0 |= 0x01<<5;break;
			case KC_RALT: bit0 |= 0x01<<6;break;
			case KC_RGUI: bit0 |= 0x01<<7;break;
			default:break;
		}
	}
	buffer[0] = bit0;
	
	while(USBD_HID_SendReport(&hUsbDeviceFS,buffer,8));
}

