#include <stdio.h>
#include <c6x.h>
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_irq.h>
#include "dsk6713.h"
#include "dsk6713_aic23.h"
#include "C6xdsk.h"
#include <math.h>
#include "ham64.h"
#include "dsp_bitrev_cplx.h"
#include "dsp_radix2.h"

#define N 64


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
void init_hw_interrupts(void);
short int mul(short int, short int, int);
void w_calc(short *);

short codec_input[N] = {0}, fft_input[2*N] = {0}, fft_output[N] = {0}, w[N] = {0};
short index[8] = {0}, re, im;
int position = 0, im2, re2;


void main()
{
	w_calc(w);
	bitrev_index(index,N);

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
	int data,i;
	short input;

	data = input_leftright_sample();
	input = (short) data;

	if(position < N){
		codec_input[position] = input;
		position ++;
	}
	if(position == N){
		position = 0;
		for(i=0; i<N ;i++){
			fft_input[2*i] = mul(codec_input[i],ham64[i],6);
			fft_input[2*i+1] = 0;
		}
		DSP_radix2(N ,fft_input ,w);
		DSP_bitrev_cplx((int*)fft_input, index, N);
		for(i=0; i<N; i++){

			re=(short)fft_input[2*i];
			im=(short)fft_input[2*i+1];

			re = mul(re, re, 0);
			im = mul(im, im, 0);

			fft_output[i]=sqrt(re + im);
		}
	}
	output_leftright_sample(data);
	return;
}

short int mul(short int m1, short int m2, int shift){
	int result1;
	short result;

	result1 = m1 * m2;
	result = result1 >> (15 + shift);
	return result;
}

void w_calc(short *array){
	int i;
	for(i=0; i<N/2; i++){
		array[2*i]= 32767 * - cos( i*2*PI/N );
		array[i*2 + 1] = 32767 * - sin( i*2*PI/N );
	}
}
