		.align 512
SPCR 	.set 0x1900008 ; SPCR ADDRESS
DRR  	.set 0x1900000 ; DRR ADDRESS
DXR  	.set 0x1900004 ; DXR ADDRESS
RCR 	.set 0x190000C ; RCR ADDRESS
XCR		.set 0x1900010 ; XCR ADDRESS

IML_pointer	.set 0x019c0004
IMH_pointer	.set 0x019c0000

buffer_left		.space 512
buffer_right	.space 512

		.def _entry
		.def int
		.ref coef
		.text

_entry:
		MVKL 0xFFFF,B0 ; CLEAR ALL PREVIOUS INTERRUPTS
		MVKH 0xFFFF,B0
		MVC B0,ICR
		ZERO B0

		MVKL 	DXR,A0  ; DXR POINTER
		MVKH 	DXR,A0

		MVKL 	DRR,A1 ;DRR POINTER
		MVKH 	DRR,A1

		MVKL IML_pointer, A3 ; IML POINTER
		MVKH IML_pointer, A3

		LDW *A3,A5  ; RINT1 -> INT4
		NOP 4
		SET A5,0,3,A5
		STW A5,*A3
		ZERO A5

		MVKL	RCR,A5	; RCR POINTER
		MVKH	RCR,A5

		MVKL	XCR,A6	; XCR POINTER
		MVKH	XCR,A6

		MVKL 	0xA0,A7	; 0xA0
		MVKH 	0xA0,A7

		STW		A7,*A5  ;SET RCR, XCR
		STW     A7,*A6

		ZERO A5
		ZERO A6
		ZERO A7

		MVKL 0X13,B1 ;SET  NMI AND INT4 TO 1
		MVC B1,IER

		MVKL 1,B2 ;SET GIE TO 1
		MVC B2,CSR

		ZERO B1
		ZERO B2

		MVKL 0x1082500, B7	;AMR
		MVKL 0x1082500, B7
		MVC B7, AMR

		MVK 0x100, B2 ;COUNTER = 100

		MVKL coef,A13 ; COEFF ADRESS
		MVKH coef,A13

loop:
		B loop
		NOP 5

int:
		LDW *A1,A4
		NOP 4
		MV B4, B5

		ZERO A14
		ZERO A15

		STH A4,*B4++	; LEFT BUFFER STORE (INPUT)

		MVKL 0x28,B0
		MVKH 0x28,B0

conv:
		LDH *--B5,A4
		LDH *+A13[A14],A5
		NOP 4
		MPY A4,A5,A6
		NOP
		SHR A6,15,A6	;Q-15 FORMAT
		ADD A6,A15,A15	;ADD RESULT

		ADD A14,1,A14	;COEFF ELEMENT COUNTER
		SUB B0,1,B0		;COEFF COUNTER
		[B0]  B conv
		NOP 5
		STH A15,*B6++	;STORE RESULT IN RIGHT BUFFER, THEN INCREMENT

		B IRP
		NOP 5



