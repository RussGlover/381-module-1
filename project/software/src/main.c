/*
 * tests.c
 *
 *  Created on: 2015-01-28
 *      Author: Tao Liu  & Aaron Cui
 */


#include <../audio_core_test/headers.h>
int main()
{

	//state machine
	screen_Init();
	sdcard_Init();
	audio_Init ();
	lcd_Init();

	tickpersec = alt_ticks_per_second();

	lcd_Printfirst(firstline);
	int w=0;
		for (w=0; w<=15;w++){
			pre_height[w] = 0;
		}
		for (w=0; w<=7;w++){
			pre_height2[w] = 0;
		}

	while (1){

		keys = keys_Detect();
		switches = switches_Detect();
		//Set trigger flags for switch0 and key1 so the input will not be read repeatedly
		switchtrigger = switch0trigger (switchstate, switches);
		switchstate = switch0state (switchstate, switches);
		keytrigger = key1trigger (keystate, keys);
		keystate = key1state (keystate, keys);
		//if (keys == Key1 && keystate == 0){
		//	keytrigger = 1;
		//	keystate = 1;
		//}
		//if (keys == 7 && keystate == 1 )
		//	keystate = 0;
		//Counters for delays and redrawn backgrounds
		//A 2 second timer
		if (counter == 1){
				counter = 0;
				timer = 1;
			}else{
				ticksincereset = alt_nticks();
				if ((ticksincereset % (2*tickpersec)) == 0){
					counter++;
				}
			}
		//A 1 second timer
		if (counter2 == 1){
				counter2 = 0;
				timer2 = 1;
		}else{
			ticksincereset = alt_nticks();
			if ((ticksincereset % tickpersec) == 0){
				counter2++;
			}
		}
		switch(state) {
			case 1:
				if(reset1 == 1){
					screen_Clear();
					draw_Menu1();
					draw_Arrow(2);
					lcd_Printsecond(case1);
					reset1 = 0;
				}
				if(timer == 1){
					draw_Background(Black);
					draw_Arrow(arrow);
					timer = 0;
				}
				//keys = IORD_8DIRECT(keyAddress,0);
				//switches = IORD_8DIRECT(switchAddress,0);
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
				if (arrow == first && switchtrigger == 1){
					state = 2;
					reset1 = 1;
					arrow = 2;
					switchtrigger = 0;
				}
				if (arrow == second && switchtrigger == 1){
					state = 3;
					reset1 = 1;
					arrow = 2;
					switchtrigger = 0;
				}

			break;

			case 2:
				if(reset2 == 1){
					screen_Clear();
					draw_Menu2();
					draw_Arrow2(2);
					lcd_Printsecond(case2);
					reset2 = 0;
				}
				if(timer == 1){
					draw_Background(Black);
					draw_Arrow2(arrow);
					timer = 0;
				}
				//keys = IORD_8DIRECT(keyAddress,0);
				//switches = IORD_8DIRECT(switchAddress,0);
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
				if (arrow == first && switchtrigger == 1){
					state = 4;
					switchtrigger = 0;
					reset2 = 1;
				}
				if (arrow == second && switchtrigger == 1){
					state = 5;
					switchtrigger = 0;
					reset2 = 1;
				}
				if (keytrigger == 1){
					state = 1;
					keytrigger = 0;
					reset2 = 1;
					arrow = 2;
				}

			break;

			case 3:
				if(reset3 == 1){
					screen_Clear();
					draw_Menu3();
					draw_Arrow2(2);
					lcd_Printsecond(case2);
					reset3 = 0;
				}
				if(timer == 1){
					draw_Background(Black);
					draw_Arrow2(arrow);
					timer = 0;
				}
				//keys = IORD_8DIRECT(keyAddress,0);
				//switches = IORD_8DIRECT(switchAddress,0);
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
				if (arrow == first && switchtrigger == 1){
					state = 6;
					switchtrigger = 0;
					reset3 = 1;
				}
				if (arrow == second && switchtrigger == 1){
					state = 7;
					switchtrigger = 0;
					reset3 = 1;
				}
				if (keytrigger == 1){
					state = 1;
					keytrigger = 0;
					reset3 = 1;
					arrow = 2;
				}

			break;

			case 4:
				if(reset4_1 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					lcd_Printsecond(drawing);
					handle = alt_up_sd_card_fopen("ab/hi.txt",false);
					reset4_1 = 0;
				}

				if(timer2 == 1){
					//draw_Background(Blue);
					draw_Axis(Yellow);
					timer2 = 0;
				}

				//keys = IORD_8DIRECT(keyAddress,0);
				sdcard_ReadFile(temp, handle);
				display_Data(temp);
				if(keytrigger == 1){
					if(reset4_2 == 1){
						sdcard_fclose(handle);
						reset4_2 = 0;
					}
					state = 2;
					arrow = 2;
					keytrigger = 0;
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
					draw_Axis2(Yellow);
					lcd_Printsecond(drawing);
					handle = alt_up_sd_card_fopen("ab/hi.txt",false);
					draw_Text(text);
					reset5_1 = 0;
				}

				if(timer2 == 1){
					//draw_Background(Blue);
					draw_Axis2(Yellow);
					timer2 = 0;
				}

				//keys = IORD_8DIRECT(keyAddress,0);
				sdcard_ReadFile2(temp2, handle);
				//***************************FFT calculation goes to here
				display_Data2(temp2,pre_height2);
				if(keytrigger == 1){
					if(reset5_2 == 1){
						sdcard_fclose(handle);
						reset5_2 = 0;
					}
					state = 2;
					arrow = 2;
					keytrigger = 0;
					reset5_1 = 1;
					reset5_2 = 1;
					for (w=0; w<=7;w++){
						pre_height2[w] = 0;
					}
				}

			break;

			case 6:
				if(reset6 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis(Yellow);
					lcd_Printsecond(drawing);
					reset6 = 0;
				}

				if(timer2 == 1){
					draw_Background2(Blue);
					draw_Axis(Yellow);
					timer2 = 0;
				}

				//keys = IORD_8DIRECT(keyAddress,0);
				audio_Readtoscreen (buffer_16, temp);
				display_Data(temp);
				if(keytrigger == 1){
					state = 3;
					arrow = 2;
					keytrigger = 0;
					reset6 = 1;
					for (w=0; w<=15;w++){
						pre_height[w] = 0;
					}
				}

				break;

			case 7:
				if(reset7 == 1){
					screen_Clear();
					draw_Background(Blue);
					draw_Axis2(Yellow);
					draw_Text(text);
					lcd_Printsecond(drawing);
					reset7 = 0;
				}

				if(timer2 == 1){
					draw_Background2(Blue);
					draw_Axis2(Yellow);
					timer2 = 0;
				}

				//keys = IORD_8DIRECT(keyAddress,0);
				//audio_Readtobuffer (temp3);

				//for(w=0; w<=1023; w++){   // for testing values stored in the temp3
				//		printf("%u \t", temp3[w]);
				//}

				// change to audio_Readtobuffer, depends on how large the array that FFT takes
				//temp3 is 1024 elements unsigned int
				//temp2 takes 8 elements short int
				//*************FFT calculation goes here
				//display_Data2(temp2,pre_height2);
				if(keytrigger == 1){
					state = 3;
					arrow = 2;
					keytrigger = 0;
					reset7 = 1;
					for (w=0; w<=7;w++){
						pre_height2[w] = 0;
					}
				}

				break;

		}

	}

  return 0;
}



