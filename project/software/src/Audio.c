/*
 * Audio.c
 *
 *  Created on: 2015-02-08
 *      Author: Allen
 */
#include <../audio_core_test/Definitions.h>
#include <../audio_core_test/Screen.h>

alt_up_audio_dev * audio_dev;

/*
 * set up audio config
 * printf to the console if it succeeds
 */
void av_config_setup(void) {
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev("/dev/audio_and_video_config_0");
	while (!alt_up_av_config_read_ready(av_config)) { }
	printf("audio configuration success \n");
}

/* open the audio device
 * printf to the console if fail or succeed
 */
void audio_Init(void) {
	av_config_setup();
	audio_dev = alt_up_audio_open_dev ("/dev/audio_0");
	if ( audio_dev == NULL)
		printf ("Error: could not open audio device \n");
	else
		printf ("Opened audio device \n");
}

/*
 * read input data from microphone and print them on console
 * Debug method
 */
void audio_Read () {
	while(1)
	{
		unsigned int temp=0;
		int fifospace = alt_up_audio_read_fifo_avail (audio_dev, ALT_UP_AUDIO_RIGHT);
		if ( fifospace > 0 ) // check if data is available
		{
			// read audio buffer
			alt_up_audio_read_fifo (audio_dev, &(temp), 1, ALT_UP_AUDIO_RIGHT);
			if(temp>300 && temp < 60000) //filter the sounds, which are too loud and too small;
			{
				printf("%u \t",temp);
			}
		}
	}

}


/*
 * read input data from microphone and store 1024 elements to an array l_buf[]
 * used for FFT calculations
 */
void audio_Readtobuffer (unsigned int r_buf[]) {
	int count =0;
	while(count<1024)
	{
		unsigned int temp=0;
		int fifospace = alt_up_audio_read_fifo_avail (audio_dev, ALT_UP_AUDIO_RIGHT);
		if ( fifospace > 0 ) // check if data is available
		{
			// read audio buffer
			alt_up_audio_read_fifo (audio_dev, &(temp), 1, ALT_UP_AUDIO_RIGHT);
			if(temp>300 && temp < 60000)
			{
				printf("%u \t",temp);
				r_buf[count] = temp;
				count++;
			}
		}
	}

}


/*
 * Read input data from microphone and store 16 elements to an array buffer
 * used for provide data for screen
 */
void audio_Readtoscreen (unsigned int buffer[]) {
	int count =0;
	while(count<16)
	{
		unsigned int temp=0;
		int fifospace = alt_up_audio_read_fifo_avail (audio_dev, ALT_UP_AUDIO_RIGHT);
		if ( fifospace > 0 ) // check if data is available
		{
			// read audio buffer
			alt_up_audio_read_fifo (audio_dev, &(temp), 1, ALT_UP_AUDIO_RIGHT);
			if(temp>300 && temp < 60000)
			{
				printf("%u \t",temp);
				buffer[count] = temp;
				count++;
			}
		}
	}
}

