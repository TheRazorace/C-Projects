/*****************************************************************************
* FILENAME
*   Delays and echo.c
*
* DESCRIPTION
*   Delays and Echo using TMS320C6713 DSK Board and AIC23 audio codec.
*   Based on sampling rate of 48000 samples per second. Delay up to 4 seconds.  */
/*********************************************************************************/

#include <stdio.h>
#include "bargraph.h"
#include "stereo.h"
#include "switches.h"
#include "c6713dsk.h"
#include "dsk6713_aic23.h"
#include "stdlib.h"
#include "math.h"
#include "csl.h"

#define N (48000 * 4)

// Codec configuration settings
DSK6713_AIC23_Config config = { \
	0x0017,  /* 0 DSK6713_AIC23_LEFTINVOL  Left line input channel volume */ \
	0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOL Right line input channel volume */\
	0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOL  Left channel headphone volume */  \
	0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOL Right channel headphone volume */ \
	0x0015,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      \
	0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     \
	0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             \
	0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ \
	0x0001,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control */            \
	0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   \
};


far signed int delay_array[N]; /* Buffer for maximum delay of 4 seconds */

/*
 Uses DIP switches to control the delay time between 0 ms and
 4 seconds. 48000 samples represent 1 second.
*/

get_delay_time(){

}

/*
Take oldest sample from the array and replace with the newest
Uses a circular buffer because a straight buffer would be too slow.
*/

delayed_input(int *array, int position){
	Uint32 echo;
	int new;

	new = position + 1;
	echo = array[new];
	echo = (short) (array[new] >> 16);
	return echo;
}


/*
Fill delay array with zeroes to prevent noise / clicks.
*/

delay_array_clear(int *array){
	int i;
	for(i=0; i<N; i++){
		array[i] = 0;
	}
	return;
}

/*
Show status on Stdout window.
*/

switch_status_display(){}


int main(void)
{
	DSK6713_AIC23_CodecHandle hCodec;

	// Initialize BSL
	DSK6713_init();

	//Start codec
	hCodec = DSK6713_AIC23_openCodec(0, &config);

	// Set  frequency to 48KHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);

	int current = 0;
	Uint32 val, prev_echo, next_echo;

	delay_array_clear(delay_array);


	*(unsigned volatile int*)McBSP1_RCR = 0xA0;
	*(unsigned volatile int*)McBSP1_XCR = 0xA0;

	while(1){
		while(!DSK6713_AIC23_read(hCodec, &val));
		delay_array[current] = val;
		next_echo = val & 0xFFFF0000;
		prev_echo = delayed_input(delay_array, current);
		val = prev_echo + next_echo;
		current++;
		if (current == N){
			current = 0;
		}

		while(!DSK6713_AIC23_write(hCodec, val));
	}
	return (0);
}










