#ifndef _MYLCD_H
#define _MYLCD_H

#include "main.h"
#include "lcd.h"
#include "touch.h"
#include "usart.h"
#include "stdio.h"

void Load_keyboard();//按键界面菜单
void Load_textshow();//show the text 
uint8_t Get_keynum();//return the push keynum
uint32_t show_number(uint8_t key_in);//按键输入值的显示



#endif