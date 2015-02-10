
#include <../audio_core_test/headers.h>
//#include <sys/alt_alarm.h>
int main()
{
	int pre_height [16] ;
	int w=0;
	for (w=0; w<=15;w++){
		pre_height[w] = 0;
	}

	//audio test
	/*
	 unsigned int  r_buf;
	   r_buf = (unsigned int ) malloc(1024*sizeof(unsigned int));
	audio_Init ();
	audio_Read();
	free(&r_buf);
	/*


/*
	int i=0;
	for(i=0;i<1024;i++){
		printf("%u \t", l_buf[i]);
	}
*/




	// sdcard test
	//sdcard_Init();
	//int temp[16];
	//short int handle=0;


	//handle = alt_up_sd_card_fopen("ab/hi.txt",false);
	//sdcard_ReadFile(temp,  handle);
	//printArray(temp);
	//sdcard_ReadFile(temp,  handle);
	//printArray(temp);
	//sdcard_ReadFile(temp,  handle);
	//sdcard_ListFiles("ab/.");
	//sdcard_ReadFile(temp,fp.file_handle);
	//printArray(temp);
	//sdcard_fclose(handle);

/*
    int i =0;
    for(i=0;i<=15;i++){
    	temp[i] = 1;
    }
	handle = alt_up_sd_card_fopen("ab/hi1.txt",true);
	printf("SD Accessed Successfully, writing data...");
	sdcard_WriteFile(temp,handle);
	printf("Done!\n");
	printf("Closing File...");
	sdcard_fclose(handle);
	printf("Done!\n");
*/


	//screen test



	//Screen_Init();
/*
	Draw_Background (Navy);
	Draw_Axis (Red);
	Draw_Bars(0,50,Green);
	Draw_Bars(1,70,Yellow);
	Draw_Bars(2,90,White);
	Draw_Bars(3,100,Purple);
	Draw_Bars(4,110,Olive);
	Draw_Bars(5,120,DarkGrey);
	Draw_Bars(6,130,Cyan);
	Draw_Bars(7,140,Orange);

	Draw_Menu();
	Draw_Arrow(1);
	Screen_Clear();
	*/



	/*
	int x=0;
	short int test[15];
	for (x=0;x<=15;x++){
		test[x]=random_double();
	}
	Display_Data(test);


	 Screen_Clear();
	 x=0;
	 	for (x=0;x<=15;x++){
	 		test[x]=random_double();
	 	}
	 Display_Data(test);

	*/



//switch

/*
   long PBchanges;
   int i;

 *switchAddress = 0; //clear out any changes so far
 while (1)
   {
      PBchanges = *switchAddress;
      // Display the state of the change register on green LEDs
      *ledAddress = PBchanges;
      if(PBchanges)
      {
         // Delay, so that we can observe the change on the LEDs
         for (i=0; i<1000000;i++);
         *switchAddress = 0; //reset the changes for next round
      }
   }
   */


	//run test

	long keychanges;
	int arrow_number =1;
	int i;
	//int x=0;
	//short int test[15];
	int handle = 0;
	short int temp[16];
	Screen_Init();
	sdcard_Init();
	Draw_Background(Black);
	Draw_Menu ();
	Draw_Arrow(arrow_number);
	while (1){
		int reset1 = 1;
		int reset2 = 1;
		int reset3 = 1;

		 keychanges = *switchAddress;
			 if (arrow_number == 1){
				 Clear_Arrows();
				 Draw_Arrow(arrow_number);
				 handle = alt_up_sd_card_fopen("ab/hi5.txt",true);
				 while(keychanges){
					 	 if (reset1){
					 		Clear_Arrows();
					 		Char_Clearonly();
					 		Draw_Write();
					 		reset1 = 0;
					 	 }
				 		sdcard_WriteFile(temp,  handle);
				 		printArray(temp);
				 		for (i=0; i<70000;i++);
				 		keychanges = 0;
				 		keychanges = *switchAddress;
				 		if (!keychanges){
				 			Draw_Background(Black);
				 			Draw_Menu ();
				 		}
				 }
				 sdcard_fclose(handle);
				 arrow_number +=1;
			 }
			 else if(arrow_number == 2){
				 Clear_Arrows();
				 Draw_Arrow(arrow_number);
				 handle = alt_up_sd_card_fopen("ab/hi.txt",false);
				 while(keychanges){
					 if (reset2){
					 		Clear_Arrows();
					 		Char_Clearonly();
					 		Draw_Read();
					 		reset2 = 0;
					 }
				 		sdcard_ReadFile(temp,  handle);
				 		printArray(temp);
				 		for (i=0; i<70000;i++);
				 		keychanges = 0;
				 		keychanges = *switchAddress;
				 		if (!keychanges){
				 				Draw_Background(Black);
				 				Draw_Menu ();
				 		}
				 }
				 sdcard_fclose(handle);
				 arrow_number +=1;
			 }
			 else{
				 Clear_Arrows();
				 Draw_Arrow(arrow_number);
				 handle = alt_up_sd_card_fopen("ab/hi.txt",false);

				 while(keychanges){
						sdcard_ReadFile(temp,  handle);
						if (reset3 ){
							Char_Clearonly();
							Draw_Background(Blue);
							Draw_Axis(Yellow);
							reset3 = 0;
						}
						Display_Data(temp);
						for (i=0; i<5000;i++);
						keychanges = 0;
						keychanges = *switchAddress;
						if (!keychanges){
								Char_Clearonly();
								Draw_Background(Black);
								Draw_Menu ();
						}
				 }

				 sdcard_fclose(handle);
				 arrow_number = 1;
			 }

		 for (i=0; i<200000;i++);
		         *switchAddress = 0;


	}




	/*
	int sw;
	while(1){
	sw = IORD_ALTERA_AVALON_PIO_DATA(keyAddress) & 0x07;
	printf("%d",sw);
		if(sw == 0)
		{
			 IOWR_ALTERA_AVALON_PIO_DATA(ledAddress,0);
		}

	}
	*/
  return 0;
}

int random_double() {
		int x = rand() % 255 + 1; //1~255
		return x;
}
