        .title  "vectors.asm"



  		.ref Int_ISR
        .ref 	_c_int00

        .sect 	"vectors"
rst:    mvkl	.s2	_c_int00,b0
        mvkh	.s2	_c_int00,b0
        b	.s2	b0
        nop
        nop
        nop
        nop
        nop



INT_1:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_2:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_3:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_4:
    	B Int_ISR
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_5:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_6:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_7:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_8:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_9:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_10:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_11:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_12:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_13:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop

INT_14:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop

INT_15:
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
  		nop
