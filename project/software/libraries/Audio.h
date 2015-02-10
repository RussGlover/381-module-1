/*
 * Audio.h
 *
 *  Created on: 2015-02-08
 *      Author: Allen
 */

#ifndef AUDIO_H_
#define AUDIO_H_

// audio configuration setup
void av_config_setup(void);

//open the audio device
void audio_Init (void);

//read input data from microphone and print them on console
void audio_Read(void);

//read input data from microphone and store 1024 samples to an array l_buf[]
void audio_Readtobuffer(unsigned int r_buf[]);

//read input data from microphone and store 16 elements to an array buffer
void audio_Readtoscreen (unsigned int buffer[]);

#endif /* AUDIO_H_ */
