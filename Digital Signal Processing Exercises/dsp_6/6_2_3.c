#include "filtro4.h"
#include <stdio.h>
#include <c6x.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "C6xdsk.h"

static DSK6713_AIC23_CodecHandle hCodec;							// Codec handle
static DSK6713_AIC23_Config config = { \
		0x0017,  /* 0 DSK6713_AIC23_LEFTINVOL  Left line input channel volume */ \
		0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOL Right line input channel volume */\
		0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOL  Left channel headphone volume */  \
		0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOL Right channel headphone volume */ \
		0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      \
		0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     \
		0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             \
		0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ \
		0x0001,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control */            \
		0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   \
	};  // Codec configuration with default settings

interrupt void serial_port_rcv_isr(void);
short int mul(short int , short int );
void init_hw_interrupts(void);
short int calc_4(short int);

short a1 = A1, a2 = A2, a3 = A3, a4 = A4;
short b1 = B1, b2 = B2, b3 = B3, b4 = B4;
short G = G_two;
short buffer_in[500] = {0}, buffer_out[500] = {0};
int current = 0;
int prev[4]= {0};
int data;

void main()
{

	DSK6713_init();		// Initialize the board support library, must be called first
	hCodec = DSK6713_AIC23_openCodec(0, &config);	// open codec and get handle
	// set codec sampling frequency 48kHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);
	*(unsigned volatile int *)McBSP1_RCR = 0x00A0;
	*(unsigned volatile int *)McBSP1_XCR = 0x00A0;
//	comm_intr();
	init_hw_interrupts();
	while(1);  // wait for interrupts

}

// interrupt service routine
void init_hw_interrupts(void)
{

	IRQ_globalDisable();			// Globally disables interrupts
	IRQ_nmiEnable();				// Enables the NMI interrupt

	// Maps an event to a physical interrupt
	// We can set the interrupt number wherever we like in vectors.asm ( this is the interrupt number )
	// Interrupt number is the second argument in IRQ_map define
	// The first argument must be set to a physical event and here we use the mcbsp1
	// and we want the receive interrupt so we have RINT1
	IRQ_map(IRQ_EVT_RINT1, 11);
	IRQ_enable(IRQ_EVT_RINT1);		// Enables the event
	IRQ_globalEnable();				// Globally enables interrupts

}

// interrupt service routine
interrupt void serial_port_rcv_isr()
{
	data = input_leftright_sample();
	// "data" contains both audio channels

	data = (short) data;
	short int  y_final = 0;

	buffer_in[current] = data;

	y_final = calc_4(data);

	buffer_out[current]= y_final;
	current++;
	if (current == 500) current = 0;

	// process "data", or pass another variable to change the output
	output_leftright_sample(y_final);

	return;

}

short int mul(short int m1, short int m2){
	short int result;
	result = (short) ((m1* m2) >> 13);

	return result;
}

short int calc_4(short int data){
	short w1, w2, y1, y2;
		//w[n] = Gx[n] + ( -a1w[n-1] - a2w[n-2] - a3w[n-3] - a4w[n-4])
		w1 = (int) mul(G,data) - (int) mul(a1, prev[0]) -(int) mul(a2, prev[1]);
		w2 = (int)w1 -(int) mul(a3, prev[2]) -(int) mul(a4, prev[3]);

		//y[n] = w[n] + ( b1w[n-1] + b2w[n-2] + b3w[n-3] + b4w[n-4] )
		y1 = (int) mul(0.25, w2) + (int) mul(b1, prev[0]) + (int) mul(b2, prev[1]);
		y2 = (int)y1 + (int) mul(b3, prev[2]) + (int) mul(b4, prev[3]);

		prev[3] = prev[2];
		prev[2] = prev[1];
		prev[1] = prev[0];
		prev[0] = w2;

		return (short)y2;
}





