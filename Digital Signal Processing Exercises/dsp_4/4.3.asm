SPCR .set 0x1900008 ; SPCR ADDRESS
DRR  .set 0x1900000 ; DRR ADDRESS

		.def _entry
		.text

_entry:	MVKL SPCR,A1
		MVKH SPCR,A1
		MVKL DRR,A2
		MVKH DRR,A2


loop:	LDW *A1,B0
		NOP 4
		AND B0,2,B0 ;CHECK FIRST BIT

		XOR B0,2,B0 ;EXIT LOOP

       	[B0]  B loop
 		NOP 5

  		LDW *A2,A0 ;LOAD VALUE TO A0
  		NOP 4

  		IDLE
  		.end
