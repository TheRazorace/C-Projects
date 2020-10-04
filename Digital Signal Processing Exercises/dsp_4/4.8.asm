transmit	.macro r1
transmit?:
			STW r1, *A0
			.endm

receive		.macro r2
receive?:
			LDW *A1, r2
			NOP 4
			.endm
