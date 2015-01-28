#include <../Module1/Definitions.h>
#include <../Module1/Screen.h>

//Example on how to read from keys and switches and write to the leds

void main()
{
	char keys;
	char switches;
	char leds = 255;

	while(1)
	{
		keys = IORD_8DIRECT(keyAddress,0);
		switches = IORD_8DIRECT(switchAddress,0);
		IOWR_8DIRECT(ledAddress,0,leds);
	}
}


