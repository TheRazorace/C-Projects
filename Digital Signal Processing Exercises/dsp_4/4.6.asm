
SPCR 	.set 0x1900008 ; SPCR ADDRESS
DRR  	.set 0x1900000 ; DRR ADDRESS
DXR  	.set 0x1900004 ; DXR ADDRESS
RCR 	.set 0x190000C  ; RCR ADDRESS
XCR		.set 0x1900010 ; XCR ADDRESS

IML_pointer	.set 0x019c0004
IMH_pointer	.set 0x019c0000

buffer_left		.space 512
buffer_right	.space 512

		.def _entry
		.def int
		.def buff
		.text

_entry:
		MVKL 0xFFFF,B0 ; CLEAR ALL PREVIOUS INTERRUPTS
		MVKH 0xFFFF,B0
		MVC B0,ICR

		MVKL 	DXR,A0  ; DXR POINTER
		MVKH 	DXR,A0

		MVKL 	DRR,A1 ;DRR POINTER
		MVKH 	DRR,A1

		MVKL IML_pointer, A3 ; IML POINTER
		MVKH IML_pointer, A3

		MVKL IMH_pointer, A4 ; IMH POINTER
		MVKH IMH_pointer, A4

		MVKL	RCR,A5	; RCR POINTER
		MVKH	RCR,A5

		MVKL	XCR,A6	; XCR POINTER
		MVKH	XCR,A6

		MVKL 	0xA0,A7	; 0xA0
		MVKH 	0xA0,A7

		STW		A7,*A5  ;SET RCR, XCR
		STW     A7,*A6

		MVKL 0X13,B1 ;SET  NMI AND INT4 TO 1
		MVC B1,IER

		MVKL 1,B2 ;SET GIE TO 1
		MVC B2,CSR

		MVKL buffer_left, A8 ;STORE LEFT BUFFER
		MVKH buffer_left, A8

		MVKL buffer_right, A9 ;STORE RIGHT BUFFER
		MVKH buffer_right, A9

		MVK 0x100, B0 ;COUNTER

		LDW *A3 ,A10
		NOP 4
		SET A10,0,3,A10
		STW A10, *A3

loop:	B loop
		NOP 5

int:
		[!B0] B buff
		NOP 5
		LDW *A1, A10
		NOP 4
		STW A10, *A0
		MV A10, A11
		SHR A11, 16, A11
		STH A10, *A9++
		STH A11, *A8++
		SUB B0, 1, B0
		B IRP
		NOP 5

buff:
		MVKL buffer_left, A8 ;STORE LEFT BUFFER
		MVKH buffer_left, A8

		MVKL buffer_right, A9 ;STORE RIGHT BUFFER
		MVKH buffer_right, A9

		MVK 0x100, B0 ;COUNTER

		B int
		NOP 5

		.end

