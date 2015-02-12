/*
 * Definitions.h
 *
 *  Created on: 2015-01-26
 *      Author: Tao Liu
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//universal variables
int state = 1;
char keys;
bool keytrigger = 0;
bool keystate = 0;
char switches;
bool switchstate = 0;
bool switchtrigger = 0;
int ticksincereset = 0;
int tickpersec;
int arrow = 2;
short int temp[16];
short int temp2[8];
unsigned int temp3[1024];
short int temp4[1024];
int i;
int counter = 0;
int timer = 1;
int timer2 = 1;
int counter2 = 0;

//Audio
unsigned buffer_16[16];

//Video
short int pre_height[16];
short int pre_height2[8];
char text[] = "The classification of the sound is: ";


//libraries
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_video_character_buffer_with_dma.h>
#include <Altera_UP_SD_Card_Avalon_Interface.h>
#include <altera_avalon_pio_regs.h>
#include <altera_up_avalon_audio.h>
#include <altera_up_avalon_audio_and_video_config.h>
#include "altera_up_avalon_character_lcd.h"

#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/alt_alarm.h>


#define switchAddress   (volatile char*)   0x00004870
#define ledAddress       (volatile char*)   0x00004860
#define keyAddress (volatile char*)   0x00004840

//screen
//alt_up_pixel_buffer_dma_dev *pixel_buffer;
//alt_up_char_buffer_dev *char_buffer;

#define Screen_Height   240;
#define Screen_Width    320;
#define drawer_base (volatile int *) 0x5000

//colours
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

//keys&pushbuttons numbers
int Key3 = 3;
int Key2 =	5;
int Key1 =	6;
int Switch0	= 1;
int Switch1	= 2;
int Switch2	= 4;

//user menu

int reset1 = 1;
int reset2 = 1;
int reset3 = 1;
int reset4_1 = 1;
int reset4_2 = 1;
int reset5_1 = 1;
int reset5_2 = 1;
int reset6 = 1;
int reset7 = 1;
int reset8 = 1;


int first = 2;
int second = 3;
int third = 4;


//SD card
int handle = 0;

//lcd
char firstline[] = " Current State:\0";
char case1[] = "   User Menu      \0";
char case2[] ="  SD Card Menu     \0";
char case3[] = "   Audio Menu     \0";
char drawing[] = "Data Displaying    \0";




#endif /* DEFINITIONS_H_ */
