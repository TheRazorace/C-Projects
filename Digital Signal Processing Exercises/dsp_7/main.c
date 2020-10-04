
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
short int mul(short int , short int, int );
void init_hw_interrupts(void);
short int Goertzel(short int* , short int, int );
int buffer_max( short int *);

int N = 205, current = 0;
short int buffer_in[205] = {0};
int f_lo[4] = {697, 770, 852, 941}, f_hi[4] = {1209, 1336, 1477, 1633};
short coef_lo[4] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7};
short coef_hi[4] = {0x4A70, 0x4090, 0x6521, 0x479C};
const char buttons[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'},
		   {'7', '8','9', 'C'}, {'*', '0', '#', 'D'}};
short int temp0 ,temp1 ,temp2 ,temp3, y;


void main()
{

	DSK6713_init();		// Initialize the board support library, must be called first
	hCodec = DSK6713_AIC23_openCodec(0, &config);	// open codec and get handle
	// set codec sampling frequency 8kHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_8KHZ);
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
	int data, i, d, index_lo, index_hi;
	short int input, spectrum_lo[4] = {0}, spectrum_hi[4] = {0};

	data = input_leftright_sample();
	input = (short) data;
	input = input >> 2;
	if( input> 5 || input < -5){

		if(current < N){
			buffer_in[current] = input;
			current ++;

		}if(current == N){

			for(i=0; i<4; i++){
				if(i>1) d = 0;
				else d = 1;

				spectrum_lo[i] = Goertzel(buffer_in, coef_lo[i], 1);
				spectrum_hi[i] = Goertzel(buffer_in, coef_hi[i], d);
			}

			index_lo = buffer_max(spectrum_lo);
			index_hi = buffer_max(spectrum_hi);

			printf("  Button: %c Low frequency: %d,   High frequency: %d\n",
				buttons[index_lo][index_hi], f_lo[index_lo], f_hi[index_hi]);
			current = 0;
		}
	}

	// "data" contains both audio channels


	//output_leftright_sample(data);
	return;
}

short int mul(short int m1, short int m2, int d){
	int result1;
	short int result;

	result1 = m1 * m2;
	result = result1 >> (15 - d);

	return result;
}

short int Goertzel(short int *buffer, short coef, int d){
	int i;
	short int q[3] = {0};

	for(i=0; i<N; i++){
		q[0] = buffer[i] + mul(q[1], coef, d) - q[2];
		q[2] = q[1];
		if(i<N-1) q[1] = q[0];
	}

	temp0 = mul(q[0], q[0], 0);
	temp1 = mul(q[1], q[1], 0);
	temp2 = mul(coef, q[0], d);
	temp3 = mul(temp2,q[1],0);

	y = temp0 + temp1 - temp3;
	return y;
}

int buffer_max( short int *buffer){
	int i, index = 0;
	short int max = 0;

	for(i=0; i<4; i++){
		if(buffer[i] > max){
			max = buffer[i];
			index = i;
		}
	}
	return index;
}
