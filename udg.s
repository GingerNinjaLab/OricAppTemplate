
_usg_data
	; 2x16
	.byt %000111
	.byt %000111
	.byt %011111
	.byt %000101
	

_setup_udgs 
(.
	ldx #8*4
loop
	lda _usg_data-1,x
	sta $9800+91*8-1,x
	dex
	bne loop
.)


