SPCR .set 0x1900008 ; SPCR ADDRESS
DXR  .set 0x1900004 ; DXR ADDRESS

		.def _entry
		.text

_entry:	MVKL SPCR, A2
		MVKH SPCR, A2
		MVKL 0x20000, A3
		MVKH 0x20000, A3
		MVKL DXR,A1
		MVKH DXR,A1

loop:	LDW *A2,B1 ; LOAD SPCR VALUE
	    NOP 4
        AND B1,A3,B1  ;CHECK 17th BIT

		XOR B1,A3,B1  ;EXIT LOOP
        [B1]  B loop
	    NOP 5

        STW A0,*A1   ; STORE VALUE TO  DXR

        IDLE
       	.end

