/*
 * tests.c
 *
 *  Created on: 2015-01-28
 *      Author: Tao Liu
 */

#include <../audio_core_test/headers.h>
int main()
{

	//state machine
	screen_Init();
	sdcard_Init();
	audio_Init ();

	int w=0;
		for (w=0; w<=15;w++){
			pre_height[w] = 0;
		}

	while (1){
		switch(state) {
			case 1:
				if(reset1 == 1){
					screen_Clear();
					draw_Menu1();
					draw_Arrow(2);
					reset1 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				switches = IORD_8DIRECT(switchAddress,0);
				if (keys == Key3 && arrow == first){
					clear_Arrows();
					draw_Arrow(3);
					arrow = second;
				}
				if (keys == Key2 && arrow == second){
					clear_Arrows();
					draw_Arrow(2);
					arrow = first;
				}
				if (arrow == first && switches == Switch0){
					state = 2;
					reset1 = 1;
					for (i=0; i<200000;i++);
				}
				if (arrow == second && switches == Switch0){
					state = 3;
					reset1 = 1;
					for (i=0; i<200000;i++);
				}

			break;

			case 2:
				if(reset2 == 1){
					screen_Clear();
					draw_Menu2();
					draw_Arrow2(2);
					reset2 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				switches = IORD_8DIRECT(switchAddress,0);
				if (keys == Key3 && arrow == first){
					clear_Arrows2();
					draw_Arrow2(3);
					arrow = second;
				}
				if (keys == Key2 && arrow == second){
					clear_Arrows2();
					draw_Arrow2(2);
					arrow = first;
				}
				if (arrow == first && switches == Switch0){
					state = 4;
					reset2 = 1;
				}
				if (arrow == second && switches == Switch0){
					state = 5;
					reset2 = 1;
				}
				if (keys == Key1){
					state = 1;
					reset2 = 1;
				}

			break;

			case 3:
				if(reset3 == 1){
					screen_Clear();
					draw_Menu3();
					draw_Arrow2(2);
					reset3 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				switches = IORD_8DIRECT(switchAddress,0);
				if (keys == Key3 && arrow == first){
					clear_Arrows2();
					draw_Arrow2(3);
					arrow = second;
				}
				if (keys == Key2 && arrow == second){
					clear_Arrows2();
					draw_Arrow2(2);
					arrow = first;
				}
				if (arrow == first && switches == Switch0){
					state = 6;
					reset3 = 1;
				}
				if (arrow == second && switches == Switch0){
					state = 7;
					reset3 = 1;
				}
				if (keys == Key1){
					state = 1;
					reset3 = 1;
				}

			break;

			case 4:
				if(reset4_1 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					handle = alt_up_sd_card_fopen("ab/hi.txt",false);
					reset4_1 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				sdcard_ReadFile(temp, handle);
				display_Data(temp);
				if(keys == Key1){
					if(reset4_2 == 1){
						sdcard_fclose(handle);
						reset4_2 = 0;
					}
					state = 2;
					reset4_1 = 1;
					reset4_2 = 1;
					for (w=0; w<=15;w++){
						pre_height[w] = 0;
					}
				}

			break;

			case 5:
				if(reset5_1 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					handle = alt_up_sd_card_fopen("ab/hi.txt",false);
					reset5_1 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				sdcard_ReadFile(temp, handle);
				//***************************FFT calculation goes to here
				display_Data(temp);
				if(keys == Key1){
					if(reset5_2 == 1){
						sdcard_fclose(handle);
						reset5_2 = 0;
					}
					state = 2;
					reset5_1 = 1;
					reset5_2 = 1;
				}

			break;

			case 6:
				if(reset6 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					reset6 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				audio_Readtoscreen (buffer_16, temp);
				printArray(temp);
				display_Data(temp);
				if(keys == Key1){
					state = 3;
					reset6 = 1;
				}

				break;

			case 7:
				if(reset7 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					reset7 = 0;
				}
				keys = IORD_8DIRECT(keyAddress,0);
				audio_Readtoscreen (buffer_16, temp); // change to audio_Readtobuffer, depends on how large the array that FFT takes
				//*************FFT calculation goes here
				display_Data(temp);
				if(keys == Key1){
					state = 3;
					reset7 = 1;
					}

				break;

		}

	}

  return 0;
}



