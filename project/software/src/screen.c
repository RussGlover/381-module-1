/*
 * screen.c
 *
 *  Created on: 2015-01-27
 *      Author: Tao Liu
 */
//#include <../audio_core_test/Definitions.h>
#include <../audio_core_test/Screen.h>
short int pre_height [16] ;

//screen
alt_up_pixel_buffer_dma_dev *pixel_buffer;
alt_up_char_buffer_dev *char_buffer;

/*
 * initialize the screen
 * open the char buffer device and pixel buffer device
 */

void screen_Init () {
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
	char_buffer = alt_up_char_buffer_open_dev("/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,PIXEL_BUFFER_BASE);
	// Swap buffers – we have to swap because there is only an API function
	// to set the address of the background buffer.
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while
	(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	// Set the 2nd buffer address
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_char_buffer_clear(char_buffer);
}

/*
 * clear the both char buffer and pixel buffer on the screen
 *
 */
void screen_Clear () {
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_char_buffer_clear(char_buffer);
}


/*
 * clear the char buffer only on the screen
 */
void char_Clearonly(){
	alt_up_char_buffer_clear(char_buffer);
}

/*
 * Take the colour parameter and draw the backgound to that colour
 */
void draw_Background(colour) {
		IOWR_32DIRECT(drawer_base,0,0); // Set x1
		IOWR_32DIRECT(drawer_base,4,0); // Set y1
		IOWR_32DIRECT(drawer_base,8,320); // Set x2
		IOWR_32DIRECT(drawer_base,12,240); // Set y2
		IOWR_32DIRECT(drawer_base,16,colour);  // Set colour
		IOWR_32DIRECT(drawer_base,20,1);  // Start drawing
		while(IORD_32DIRECT(drawer_base,20)==0); // wait until done
}

/*
 * draw the user menu
 */
void draw_Menu1 () {
		alt_up_char_buffer_string(char_buffer, "*Analyse the Data from SD Card*", 25, 30);
		alt_up_char_buffer_string(char_buffer, "*Analyse the Data from Mic Input*", 25, 35);
		alt_up_char_buffer_string(char_buffer, "User Menu:", 30, 50);
		alt_up_char_buffer_string(char_buffer, "Key2: move up  Key3: move down  Switch0: confirm   Key1: Back to Last Menu", 5, 55);
}

/*
 * draw read from sd card menu
 */
void draw_Menu2(){
	alt_up_char_buffer_string(char_buffer, "*Analyse the Data from SD card in Time Domain*", 20, 30);
	alt_up_char_buffer_string(char_buffer, "*Analyse the Data from SD card in Frequency Domain*", 20, 35);
}

/*
 * draw write to sd card meno
 */
void draw_Menu3(){
	alt_up_char_buffer_string(char_buffer, "*Analyse the Data from Mic in Time Domain*", 20, 30);
	alt_up_char_buffer_string(char_buffer, "*Analyse the Data from Mic in Frequency Domain*", 20, 35);
}


/*
 * draw cursor on the screen
 */
void draw_Arrow (int y){  //Y could be 1,2,3,4 which means it points the 1st,2nd,3rd or 4th item on menu
	int amplitude=20*y+80;
	IOWR_32DIRECT(drawer_base,0,22*4);
	IOWR_32DIRECT(drawer_base,4,amplitude);
	IOWR_32DIRECT(drawer_base,8,23*4);
	IOWR_32DIRECT(drawer_base,12,amplitude);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

	IOWR_32DIRECT(drawer_base,0,23*4-2);
	IOWR_32DIRECT(drawer_base,4,amplitude-1);
	IOWR_32DIRECT(drawer_base,8,23*4-1);
	IOWR_32DIRECT(drawer_base,12,amplitude-1);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

	IOWR_32DIRECT(drawer_base,0,23*4-2);
	IOWR_32DIRECT(drawer_base,4,amplitude+1);
	IOWR_32DIRECT(drawer_base,8,23*4-1);
	IOWR_32DIRECT(drawer_base,12,amplitude+1);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

}
void draw_Arrow2 (int y){  //Y could be 1,2,3,4 which means it points the 1st,2nd,3rd or 4th item on menu
	int amplitude=20*y+80;
	IOWR_32DIRECT(drawer_base,0,17*4);
	IOWR_32DIRECT(drawer_base,4,amplitude);
	IOWR_32DIRECT(drawer_base,8,18*4);
	IOWR_32DIRECT(drawer_base,12,amplitude);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

	IOWR_32DIRECT(drawer_base,0,18*4-2);
	IOWR_32DIRECT(drawer_base,4,amplitude-1);
	IOWR_32DIRECT(drawer_base,8,18*4-1);
	IOWR_32DIRECT(drawer_base,12,amplitude-1);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

	IOWR_32DIRECT(drawer_base,0,18*4-2);
	IOWR_32DIRECT(drawer_base,4,amplitude+1);
	IOWR_32DIRECT(drawer_base,8,18*4-1);
	IOWR_32DIRECT(drawer_base,12,amplitude+1);
	IOWR_32DIRECT(drawer_base,16,White);
	IOWR_32DIRECT(drawer_base,20,1);

}

/*
 * clear the cursor
 *
 */
void clear_Arrows(){
	IOWR_32DIRECT(drawer_base,0,22*4); // Set x1
	IOWR_32DIRECT(drawer_base,4,24*4); // Set y1
	IOWR_32DIRECT(drawer_base,8,24*4); // Set x2
	IOWR_32DIRECT(drawer_base,12,36*4); // Set y2
	IOWR_32DIRECT(drawer_base,16,Black);  // Set colour
	IOWR_32DIRECT(drawer_base,20,1);  // Start drawing
	while(IORD_32DIRECT(drawer_base,20)==0); // wait until done

}

void clear_Arrows2(){
	IOWR_32DIRECT(drawer_base,0,17*4); // Set x1
	IOWR_32DIRECT(drawer_base,4,24*4); // Set y1
	IOWR_32DIRECT(drawer_base,8,19*4); // Set x2
	IOWR_32DIRECT(drawer_base,12,36*4); // Set y2
	IOWR_32DIRECT(drawer_base,16,Black);  // Set colour
	IOWR_32DIRECT(drawer_base,20,1);  // Start drawing
	while(IORD_32DIRECT(drawer_base,20)==0); // wait until done

}

/*
 * draw the axis for the histogram
 */
void draw_Axis (int colour) {
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

	alt_up_char_buffer_string(char_buffer, "25", 8, 47);
	alt_up_char_buffer_string(char_buffer, "50", 8, 42);
	alt_up_char_buffer_string(char_buffer, "75", 8, 37);
	alt_up_char_buffer_string(char_buffer, "100", 7, 32);
	alt_up_char_buffer_string(char_buffer, "125", 7, 27);
	alt_up_char_buffer_string(char_buffer, "150", 7, 22);
	alt_up_char_buffer_string(char_buffer, "175", 7, 17);
	alt_up_char_buffer_string(char_buffer, "200", 7, 12);
	alt_up_char_buffer_string(char_buffer, "225", 7, 7);
	alt_up_char_buffer_string(char_buffer, "250", 7, 2);




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


/*
 * Take the input of 16 elements array
 * draw 16 blocks on the histogram
 */
void display_Data(short int data[]){

	int i;
	short int height;
	double scale=0.8;
	for (i=0; i<=15;i++){
		height=(short int)(data[i]*scale);
		draw_Bars(i,height,Green,pre_height); //change the colour
		pre_height[i] = height;
	}
}

/*
 * draw single bar on the screen depends on the color and x coordinates and height parameter
 */
void draw_Bars (int bar_num,short int height,int colour,short int pre_height[]){ //x indicate the number of the bar, which is 0,1,2,3,etc    height is selected from 0-209
	int n = 42+15*bar_num;
	if (pre_height[bar_num] < height){
		IOWR_32DIRECT(drawer_base,0,n);
		IOWR_32DIRECT(drawer_base,4,209 - pre_height[bar_num]);
		IOWR_32DIRECT(drawer_base,8,n+13);
		IOWR_32DIRECT(drawer_base,12,209 - height);
		IOWR_32DIRECT(drawer_base,16,colour);
		IOWR_32DIRECT(drawer_base,20,1);
		while(IORD_32DIRECT(drawer_base,20)==0);
	}
	else {
		IOWR_32DIRECT(drawer_base,0,n);
		IOWR_32DIRECT(drawer_base,4,209-height);
		IOWR_32DIRECT(drawer_base,8,n+13);
		IOWR_32DIRECT(drawer_base,12,209-pre_height[bar_num]);
		IOWR_32DIRECT(drawer_base,16,Blue);     //cover with background colour
		IOWR_32DIRECT(drawer_base,20,1);
		while(IORD_32DIRECT(drawer_base,20)==0);
	}

}

/*
 * draw error of cursor moving up
 */
void draw_Errormoveup(void) {
	alt_up_char_buffer_string(char_buffer, "***Error!!! Moving up***", 30, 20);
}
