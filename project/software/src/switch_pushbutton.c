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

char keys_Detect(){
	return IORD_8DIRECT(keyAddress,0);

}

char switches_Detect (){
	return IORD_8DIRECT(switchAddress,0);
}

bool switch0trigger (bool switchstate, char switches){

	bool trigger = 0;
	if (switchstate == 0 && switches == 1 ){
		trigger = 1;
	}


	return trigger;
}

bool switch0state (bool switchstate, char switches){

	if (switchstate == 0 && switches == 1 ){
		switchstate = 1;
		//switchtrigger = 1;
	}
	if (switchstate == 1 && !(switches == 1))
		switchstate = 0;

	return switchstate;
}

#endif /* SWITCH_PUSHBUTTON_C_ */
