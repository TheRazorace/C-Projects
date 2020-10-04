SPCR .set 0x1900008 ; SPCR ADDRESS
DRR  .set 0x1900000 ; DRR ADDRESS.
DXR  .set 0x1900004 ; DXR ADDRESS

		.def _entry
		.text

_entry: MVKL DXR,A0
		MVKH DXR,A0

		MVKL DRR,A1
		MVKH DRR,A1

		MVKL SPCR,A2
		MVKH SPCR,A2

		MVKL 0x20000, A3
		MVKH 0x20000, A3

loop3:

loop2:	LDW *A2,B0
		NOP 4
		AND B0,2,B0 ;CHECK FIRST BIT
		XOR B0,2,B0 ;EXIT LOOP
       	[B0]  B loop2
 		NOP 5
  		LDW *A1,A4 ;LOAD VALUE TO  A4
  		NOP 4

loop1:	LDW *A2,B1 ; LOAD SPCR VALUE
	    NOP 4

        AND B1,A3,B1  ;CHECK 17th BIT
		XOR B1,A3,B1  ;EXIT LOOP
        [B1]  B loop1
	    NOP 5
        STW A4,*A0   ; STORE VALUE TO  DXR

        B loop3
        NOP 5
  		IDLE

  		.end
