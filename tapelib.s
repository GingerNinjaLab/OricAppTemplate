

#include "unirom.h"



_catalog_tape
    lda $9C
    ldy $9D
    sta $00
    sty $01
    php
    jsr $E725
    jsr $E6CA
    jsr £9723
    jsr $E804
    plp
    ldx $00 
    lda $01
    sta $9D
    stx $9C
    pla
    pla
    jmp $C96B
    jsr $E563
    lda #$6E
    ldy #$97
    jsr $E576
    jsr $E696
    jsr $e630
    cmp #$24
    bne $9730
    ldx #$09
    jsr $e630
    sta $5D,x
    dex
    bne $9739
    jsr $e630
    beq $974E
    sta $49,x
    sta $9781,x
    inx
    bne $9741
    sta $49,x
    sta $9781,x
    jsr $E6F0
    tax
    bne $975D
    jsr $E4D8
    rts
    lda #$B1
    ldy #$97
    jsr $CBED
    lda #$7D
    ldy #$97
    jsr $CBED
    jmp $972D
    




$2e0
