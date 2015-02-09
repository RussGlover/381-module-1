/*
 * Audio.c
 *
 *  Created on: 2015-02-08
 *      Author: Allen
 */
#include <../audio_core_test/Definitions.h>
#include <../audio_core_test/Screen.h>

alt_up_audio_dev * audio_dev;


void av_config_setup(void) {
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev("/dev/audio_and_video_config");
	while (!alt_up_av_config_read_ready(av_config)) { }
	printf("audio configuration success \n");
}

void audio_Init(void) {
	av_config_setup();
	audio_dev = alt_up_audio_open_dev ("/dev/audio");
	if ( audio_dev == NULL)
		printf ("Error: could not open audio device \n");
	else
		printf ("Opened audio device \n");
}

void audio_Read (unsigned int l_buf[]) {
	int count =0;
	//while(count<1024)
	while(1)
	{
		unsigned int temp;
		int fifospace = alt_up_audio_read_fifo_avail (audio_dev, ALT_UP_AUDIO_RIGHT);

		if ( fifospace > 0 ) // check if data is available
		{
			// read audio buffer
			//alt_up_audio_read_fifo (audio_dev, &(r_buf), 15, ALT_UP_AUDIO_RIGHT);
			alt_up_audio_read_fifo (audio_dev, &(temp), 1, ALT_UP_AUDIO_LEFT);
			if(temp>300 && temp < 60000){
				printf("%u \t",temp);
				//l_buf[count] = temp;
				//count++;
			}
		}
	}

}
