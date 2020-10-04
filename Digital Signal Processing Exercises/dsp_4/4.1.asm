RCR 	.set 0x190000C  ; Address of RCR
XCR		.set 0x1900010 ; Address of XCR
a		.set 0x000000A0 ; 5 hex

		.def _entry
		.text


_entry:	MVKL 	a,A1
		MVKH 	a,A1
		MVKL	RCR, A2
		MVKH	RCR , A2
		STW 	A1,*A2

		MVKL	XCR, A4
		MVKH	XCR , A4
		STW		A1, *A4

		IDLE
		.end
