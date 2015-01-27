/*
 * screen.c
 *
 *  Created on: 2015-01-27
 *      Author: Allen
 */
#include <../Module1/Definitions.h>
#include <../Module1/Screen.h>

//screen
alt_up_pixel_buffer_dma_dev *pixel_buffer;
alt_up_char_buffer_dev *char_buffer;
void Screen_Init () {
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
	char_buffer = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	// Set the background buffer address – Although we don’t use the background,
	// they only provide a function to change the background buffer address, so
	// we must set that, and then swap it to the foreground.
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
	PIXEL_BUFFER_BASE);
	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	// Wait for the swap to complete
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

void Screen_Clear () {
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

void Draw_Background(colour) {
	int x,y;
	for(y=0; y < 240 ; y++) {
		for(x=0; x < 320 ; x++){
			IOWR_32DIRECT(drawer_base,0,x); // Set x1
			IOWR_32DIRECT(drawer_base,4,y); // Set y1
			IOWR_32DIRECT(drawer_base,8,x); // Set x2
			IOWR_32DIRECT(drawer_base,12,y); // Set y2
			IOWR_32DIRECT(drawer_base,16,colour);  // Set colour
			IOWR_32DIRECT(drawer_base,20,1);  // Start drawing
			while(IORD_32DIRECT(drawer_base,20)==0); // wait until done
		}
	}
}

void Draw_Menu () {

		alt_up_char_buffer_string(char_buffer, "*Read Data from SD Card*", 30, 25);
		alt_up_char_buffer_string(char_buffer, "*Analyze the Data*", 30, 30);
		alt_up_char_buffer_string(char_buffer, "*Store Data onto SD Card*", 30, 35);


}

void Draw_Arrow (int y){  //Y could be 25, 30, 35
	alt_up_char_buffer_string(char_buffer, "->", 27, y);

}
void Draw_Bars (int bar_num,int height,int colour){ //x indicate the number of the bar, which is 0,1,2,3,etc    height is selected from 0-209
	int n = 42+15*bar_num;
	IOWR_32DIRECT(drawer_base,0,n);
	IOWR_32DIRECT(drawer_base,4,209-height);
	IOWR_32DIRECT(drawer_base,8,n+13);
	IOWR_32DIRECT(drawer_base,12,209);
	IOWR_32DIRECT(drawer_base,16,colour);
	IOWR_32DIRECT(drawer_base,20,1);
	while(IORD_32DIRECT(drawer_base,20)==0);
}
void Draw_Axis (int colour) {
	alt_up_char_buffer_string(char_buffer, "0", 9, 53);//x-axis
	alt_up_char_buffer_string(char_buffer, "1", 13, 54);
	alt_up_char_buffer_string(char_buffer, "2", 17, 54);
	alt_up_char_buffer_string(char_buffer, "3", 21, 54);
	alt_up_char_buffer_string(char_buffer, "4", 25, 54);
	alt_up_char_buffer_string(char_buffer, "5", 29, 54);
	alt_up_char_buffer_string(char_buffer, "6", 32, 54);
	alt_up_char_buffer_string(char_buffer, "7", 36, 54);
	alt_up_char_buffer_string(char_buffer, "8", 40, 54);
	alt_up_char_buffer_string(char_buffer, "9", 44, 54);
	alt_up_char_buffer_string(char_buffer, "10", 47, 54);
	alt_up_char_buffer_string(char_buffer, "11", 51, 54);
	alt_up_char_buffer_string(char_buffer, "12", 54, 54);
	alt_up_char_buffer_string(char_buffer, "13", 58, 54);
	alt_up_char_buffer_string(char_buffer, "14", 62, 54);
	alt_up_char_buffer_string(char_buffer, "15", 66, 54);
	alt_up_char_buffer_string(char_buffer, "16", 70, 54);

	alt_up_char_buffer_string(char_buffer, "1", 8, 47);
	alt_up_char_buffer_string(char_buffer, "2", 8, 42);
	alt_up_char_buffer_string(char_buffer, "3", 8, 37);
	alt_up_char_buffer_string(char_buffer, "4", 8, 32);
	alt_up_char_buffer_string(char_buffer, "5", 8, 27);
	alt_up_char_buffer_string(char_buffer, "6", 8, 22);
	alt_up_char_buffer_string(char_buffer, "7", 8, 17);
	alt_up_char_buffer_string(char_buffer, "8", 8, 12);
	alt_up_char_buffer_string(char_buffer, "9", 8, 7);
	alt_up_char_buffer_string(char_buffer, "10", 8, 2);




	IOWR_32DIRECT(drawer_base,0,40); //y-axis
	IOWR_32DIRECT(drawer_base,4,0);
	IOWR_32DIRECT(drawer_base,8,41);
	IOWR_32DIRECT(drawer_base,12,210);
	IOWR_32DIRECT(drawer_base,16,colour);
	IOWR_32DIRECT(drawer_base,20,1);
	while(IORD_32DIRECT(drawer_base,20)==0);

	int h = 0;
	for (h = 9; h<=205; h=h+20){ //points on y
		IOWR_32DIRECT(drawer_base,0,39);
		IOWR_32DIRECT(drawer_base,4,h);
		IOWR_32DIRECT(drawer_base,8,40);
		IOWR_32DIRECT(drawer_base,12,h+1);
		IOWR_32DIRECT(drawer_base,16,colour);
		IOWR_32DIRECT(drawer_base,20,1);
		while(IORD_32DIRECT(drawer_base,20)==0);
	}

	IOWR_32DIRECT(drawer_base,0,40);//x-axis
	IOWR_32DIRECT(drawer_base,4,211);
	IOWR_32DIRECT(drawer_base,8,320);
	IOWR_32DIRECT(drawer_base,12,210);
	IOWR_32DIRECT(drawer_base,16,colour);
	IOWR_32DIRECT(drawer_base,20,1);
	while(IORD_32DIRECT(drawer_base,20)==0);

	int i =0 ;
	for (i=55; i<320; i=i+15){ //points on x
		IOWR_32DIRECT(drawer_base,0,i);
		IOWR_32DIRECT(drawer_base,4,212);
		IOWR_32DIRECT(drawer_base,8,i+1);
		IOWR_32DIRECT(drawer_base,12,211);
		IOWR_32DIRECT(drawer_base,16,colour);
		IOWR_32DIRECT(drawer_base,20,1);
		while(IORD_32DIRECT(drawer_base,20)==0);
	}

}
