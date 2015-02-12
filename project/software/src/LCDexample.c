/*
 * Simple LCD display
 *
 * By aaron
 */


#include <../buttonTest/Definitions.h>
#include <../buttonTest/Screen.h>
//#include <../buttonTest/lcd.h>
//#include <../buttonTest/lcd.c>
#include "altera_up_avalon_character_lcd.h"

//Example on how to read from keys and switches and write to the leds

void LCD_DISPLAY(char displayLine1[], char displayLine2[])
{
	//char toDisplay[];
	//toDisplay = "1234567890abcd\0";

	//char displayLine1[] = displayLine1;
	//char displayLine2[] = "seriously plz\0";


	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Opened character LCD device\n");

	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);

	/* Write "Welcome to" in the first row */
	alt_up_character_lcd_string(char_lcd_dev, displayLine1);

	/* Write "the DE2 board" in the second row */
	//char second_row[] = "the DE2 board\0";
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, displayLine2);



	//use this to take off cursor
	alt_up_character_lcd_cursor_off(char_lcd_dev);

	//Use this to have a blinky cursor
	//alt_up_character_lcd_cursor_blink_on(char_lcd_dev);


}

void main()
{


	char line1[] = "Hi guise\0";
	char line2[] = "LCD working\0";
	LCD_DISPLAY(line1, line2);

	/*	char keys;
	char switches;
	char leds;

	 *
	 * while(1)
	{
		//IOWR_8DIRECT (lcdAddress, 0, 'a');
		keys = IORD_8DIRECT(keyAddress,0);
		//if(keys == 3){
			//printf("pushbutton 3 is activated");
		//}
		switches = IORD_8DIRECT(switchAddress,0);
		leds = switches;
		if (leds == 1)
			IOWR_8DIRECT(ledAddress,0,leds);
		if (leds == 2)
			IOWR_8DIRECT(ledAddress,0,leds);
		if (leds == 4)
			IOWR_8DIRECT(ledAddress,0,leds);

		//printf ("hello");
	}*/
}


