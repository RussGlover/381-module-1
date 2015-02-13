#include "headers.h"

signed int euclidean(short int bin[8], short int classifier[8]){
	int i;
	double sum = 0;
	for(i = 0; i < 8; i++){
		sum += pow(((double)bin[i] - (double)classifier[i]), 2);
	}
	return pow(sum, 0.5);
}

int main()
{
	short int display[8];
	//state machine
	screen_Init();
	sdcard_Init();
	audio_Init ();
	lcd_Init();

	lcd_Printfirst(firstline);
	int w=0;
		for (w=0; w<=15;w++){
			pre_height[w] = 0;
		}
		for (w=0; w<=7;w++){
			pre_height2[w] = 0;
		}

	while (1){

		if (switchstate == 0 && switches == Switch0 ){
			switchstate = 1;
			switchtrigger = 1;
		}
		if (switchstate == 1 && switches == 0)
			switchstate = 0;

		if (keys == Key1 && keystate == 0){
			keytrigger = 1;
			keystate = 1;
		}

		if (keys == 7 && keystate == 1 )
			keystate = 0;


		if (counter == 1){
				counter = 0;
				usleep (65000);
				timer = 1;
			}else{
				counter++;
			}
		if (counter2 == 1){
				counter2 = 0;
				usleep (65000);
				timer2 = 1;
		}else{
			counter2++;
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
					switchtrigger = 0 ;
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
				keys = IORD_8DIRECT(keyAddress,0);
				switches = IORD_8DIRECT(switchAddress,0);
				if (keys == Key3 && arrow == first){
					clear_Arrows2();
					draw_Arrow2(2);
					//arrow = second;
					arrow = first;
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

				keys = IORD_8DIRECT(keyAddress,0);
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

				keys = IORD_8DIRECT(keyAddress,0);
				sdcard_ReadFile2(temp4, handle);
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
					//draw_Background2(Blue);
					draw_Axis(Yellow);
					timer2 = 0;
				}

				keys = IORD_8DIRECT(keyAddress,0);
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
					//draw_Background2(Blue);

					draw_Axis2(Yellow);
				}

				keys = IORD_8DIRECT(keyAddress,0);
				audio_Readtobuffer (temp3);
				fft_engine(temp3, results);

				results[0] = results[1];
				index = 0;
				for(j = 0; j < 512; j += 64){
				        for(k = 0; k < 64; k++)
				                temp2[index] += results[j+k];
				        		display[index] = temp2[index]/50;
				        index++;
				}
//				index = 0;
//				display[index] = 0;
//				for(k = 0; k < 2; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 4; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 8; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 16; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 32; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(k = 0; 64 < 2048; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 128; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//				for(; k < 256; k++){
//					display[index] += results[k];
//				}
//				display[index];
//				index++;
//
//				max = 0;
//				for(k = 0; k < 8; k++){
//					if (max < display[index])
//						max = display[index];
//				}
//
//				max = max/200;
//				for(k = 0; k < 8; k++){
//					display[k] /= max;
//				}


				max = 0;
				for(j = 0; j < 8; j++){
				        if (temp2[j] > max){
				                max = temp2[j];
				        }
				}

				scaling_factor = 10000/((double) max);

				for(j = 0; j < 8; j++){
					//printf("pre-scale: Index: %i, %d", j, temp2[j]);
					//printf("Cast: %lf ", (scaling_factor * (double) temp2[j]));
					temp2[j] = (short)(scaling_factor * (double) temp2[j]);
					if (j == 7)
						temp2[j] /= 10;
					printf("post-scale: Index: %i, %d", j, temp2[j]);
				}

				if(timer2 == 1){
					if (euclidean(temp2, classical) > euclidean(temp2, pop)){
						char_Clearonly();
						draw_Axis2(Yellow);
						draw_Text(pop_text);
					}
					else{
						char_Clearonly();
						draw_Axis2(Yellow);
						draw_Text(classical_text);
					}
					timer2 = 0;
				}
				/*
				for(w=0; w<=1023; w++){   // for testing values stored in the temp3
						printf("%u \t", temp3[w]);
				}
				*/
				// change to audio_Readtobuffer, depends on how large the array that FFT takes
				//temp3 is 1024 elements unsigned int
				//temp2 takes 8 elements short int
				//*************FFT calculation goes here
				display_Data2(display,pre_height2);
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



