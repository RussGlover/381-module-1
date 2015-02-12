/*
 * Screen.h
 *
 *  Created on: 2015-01-26
 *      Author: Tao Liu
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_video_character_buffer_with_dma.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/alt_alarm.h>

#define drawer_base (volatile int *) 0x5000
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Background		0x0000       //black

void screen_Init (void);
void screen_Clear (void);
void draw_Menu1 (void) ;
void draw_Arrow (int y);
void draw_Arrow2 (int y);
void draw_Bars (int x,short int height,int colour,short int pre_height[]);
void draw_Bars2 (int x,short int height,int colour,short int pre_height[]);
void draw_Axis (int colour);
void draw_Axis2 (int colour);
void draw_Background(int colour);
void draw_Background2(int colour);
void display_Data (short int data[]);
void display_Data2 (short int data[], short int pre_height2[]);
void char_Clearonly(void);
void draw_Menu2(void);
void draw_Menu3(void);
void clear_Arrows(void);
void clear_Arrows2(void);
void draw_Errormoveup(void);
void draw_Text(char array[]);
#endif /* SCREEN_H_ */
