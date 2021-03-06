/*
 * SDcard.h
 *
 *  Created on: 2015-01-26
 *      Author: Tao Liu
 */

#ifndef SDCARD_H_
#define SDCARD_H_
#include <Altera_UP_SD_Card_Avalon_Interface.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/alt_alarm.h>


void sdcard_Init(void);
int sdcard_isPresent(void);
int sdcard_isFAT16(void);
short int sdcard_FirstFile(char *directory, char *file_name);
short int sdcard_NextFile(char *file_name);
int sdcard_FileSize(short int file_handle);
void sdcard_ReadFile(short int read_data [], short int file_handle);
short int sdcard_ReadByte(short int file_handle);
void sdcard_WriteFile(short int write_data [], short int file_handle);
void sdcard_ListFiles(char *directory);

short int sdcard_fopen(char *name, bool create_new_if_not_exist);
void sdcard_fclose(short int file_handle);
short int sdcard_getFattributes(short int file_handle);
void sdcard_ReadFile2(short int read_data[], short int file_handle);
void printArray(short int a[]);
typedef struct
{
	char *file_name;
	char *directory;
	short int attributes;
	short int file_handle;
	int file_size;

} File;


#endif /* SDCARD_H_ */
