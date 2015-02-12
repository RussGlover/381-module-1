/*
 * switch_pushbutton.h
 *
 *  Created on: 2015-02-10
 *      Author: Allen & Aaron
 */

#ifndef SWITCH_PUSHBUTTON_H_
#define SWITCH_PUSHBUTTON_H_


#define switchAddress   (volatile char*)   0x00004870
#define ledAddress       (volatile char*)   0x00004860
#define keyAddress (volatile char*)   0x00004840
#include <altera_avalon_pio_regs.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/alt_alarm.h>

char switches_Detect();
char keys_Detect();
bool switch0trigger (bool switchstate, char switches);
bool switch0state (bool switchstate, char switches);
bool key1trigger (bool keystate, char keys);
bool key1state (bool keystate, char keys);


#endif /* SWITCH_PUSHBUTTON_H_ */
