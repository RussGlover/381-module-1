/*
 * switch_pushbutton.c
 *
 *  Created on: 2015-02-10
 *      Author: Allen
 */

#ifndef SWITCH_PUSHBUTTON_C_
#define SWITCH_PUSHBUTTON_C_
//#include <../audio_core_test/Definitions.h>
#include <../audio_core_test/switch_pushbutton.h>

void switchpushbutton_Detect(char keys, char switches){
	keys = IORD_8DIRECT(keyAddress,0);
	switches = IORD_8DIRECT(switchAddress,0);
}

#endif /* SWITCH_PUSHBUTTON_C_ */
