#include "filtro.h"
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
short int calc(short int);

short a1_1 = A1_1, a1_2 = A1_2, a2_1 = A2_1, a2_2 = A2_2;
short b1_1 = B1_1, b1_2 = B1_2, b2_1 = B2_1, b2_2 = B2_2;
short G1 = G1_two, G2 = G2_two;
short buffer_in[500] = {0}, buffer_out[500] = {0};
int current = 0;
short prev1[2]= {0}, prev2[2] = {0};
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

	y_final = calc(data);

	buffer_out[current]= y_final;
	current++;
	if (current == 500) current = 0;

	// process "data", or pass another variable to change the output
	output_leftright_sample(y_final);

	return;

}

short int mul(short int m1, short int m2){
	short int result;

	m1 = m1 << 1;
	result = (short) (m1* (int)m2 >> 15);

	return result;
}

short int calc(short int data){
	short int w1, w2, y1, y2;
		//w1[n] = Gx[n] + ( -a1w1[n-1] - a2w1[n-2] )
		w1 = mul(G1,data) + ( - mul(a1_1, prev1[0]) - mul(a1_2, prev1[1]) );

		//y1[n] = w[n] + ( b1w1[n-1] + b2w1[n-2] )
		y1 = w1 + mul(b1_1, prev1[0]) + mul(b1_2, prev1[1]);

		prev1[1] = prev1[0];
		prev1[0] = w1;


		//w2[n] = Gy[n] + ( -a1w2[n-1] - a2w2[n-2] )
		w2 = mul(G2,y1) + ( - mul(a2_1, prev2[0]) - mul(a2_2, prev2[1]) );

		//y2[n] = w2[n] + ( b1w2[n-1] + b2w2[n-2] )
		y2 = w2 + mul(b2_1, prev2[0]) + mul(b2_2, prev2[1]);

		prev2[1] = prev2[0];
		prev2[0] = w2;

		return y2;
}





