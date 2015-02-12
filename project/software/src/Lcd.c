/*
 * Simple LCD display
 *
 * By aaron
 */

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
alt_up_character_lcd_dev * char_lcd_dev;

void lcd_Init(void) {
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL)
		printf ("Error: could not open character LCD device\n");
	else
		printf ("Opened character LCD device\n");

	alt_up_character_lcd_cursor_off(char_lcd_dev);
}

void lcd_Printfirst(char first[]){
	alt_up_character_lcd_init (char_lcd_dev);

	alt_up_character_lcd_string(char_lcd_dev, first);
}

void lcd_Printsecond(char second[]){
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, second);
}


