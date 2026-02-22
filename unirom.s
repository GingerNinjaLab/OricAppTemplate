
#include "unirom.h"



_u_test
	ldy #2
    jsr _LoadOneParam
    jmp ROM1_0_ROUTINE_____INK  ;Jump to ROM 1.0        routine
    lda $2e0       ;Return error from Graphics or sound 
    tax
	lda #0
    rts

;CLS function - No Parameters
;==============================================================
_u_cls
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq cls_rom1_1
    jmp ROM1_0_ROUTINE_____CLS      ;Jump to ROM 1.0 routine
    rts
cls_rom1_1
    jmp ROM1_1_ROUTINE_____CLS      ;Jump to ROM 1.1 routine
    rts


;TEXT function - No Parameters
;==============================================================
_u_text
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq text_rom1_1
    jmp ROM1_0_ROUTINE____TEXT      ;Jump to ROM 1.0 routine
    rts
text_rom1_1
    jmp ROM1_1_ROUTINE____TEXT      ;Jump to ROM 1.1 routine
    rts


;LORES function - No Parameters
;==============================================================
_u_lores
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq lores_rom1_1
    jmp ROM1_0_ROUTINE___LORES      ;Jump to ROM 1.0 routine
    rts
lores_rom1_1
    jmp ROM1_1_ROUTINE___LORES      ;Jump to ROM 1.1 routine
    rts


;HIRES function - No Parameters
;==============================================================
_u_hires
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq hires_rom1_1
    jmp ROM1_0_ROUTINE___HIRES      ;Jump to ROM 1.0 routine
    rts
hires_rom1_1
    jmp ROM1_1_ROUTINE___HIRES      ;Jump to ROM 1.1 routine
    rts


;PING function - No Parameters
;==============================================================
_u_ping
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq ping_rom1_1
    jmp ROM1_0_ROUTINE____PING      ;Jump to ROM 1.0 routine
    rts
ping_rom1_1
    jmp ROM1_1_ROUTINE____PING      ;Jump to ROM 1.1 routine
    rts


;ZAP function - No Parameters
;==============================================================
_u_zap
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq zap_rom1_1
    jmp ROM1_0_ROUTINE_____ZAP      ;Jump to ROM 1.0 routine
    rts
zap_rom1_1
    jmp ROM1_1_ROUTINE_____ZAP      ;Jump to ROM 1.1 routine
    rts


;SHOOT function - No Parameters
;==============================================================
_u_shoot
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq shoot_rom1_1
    jmp ROM1_0_ROUTINE___SHOOT      ;Jump to ROM 1.0 routine
    rts
shoot_rom1_1
    jmp ROM1_1_ROUTINE___SHOOT      ;Jump to ROM 1.1 routine
    rts


;EXPLODE function - No Parameters
;==============================================================
_u_explode
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq explode_rom1_1
    jmp ROM1_0_ROUTINE_EXPLODE      ;Jump to ROM 1.0 routine
    rts
explode_rom1_1
    jmp ROM1_1_ROUTINE_EXPLODE      ;Jump to ROM 1.1 routine
    rts

;INK function - 
;   Param1: Colour
;==============================================================
_u_ink
;    jmp get1Params
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq ink_rom1_1
    jsr _LoadOneParam
    jmp ROM1_0_ROUTINE_____INK      ;Jump to ROM 1.0 routine
    jsr _SetResultParam             
    rts 

ink_rom1_1
    jsr _LoadOneParam
    jmp ROM1_1_ROUTINE_____INK      ;Jump to ROM 1.1 routine    
    jsr _SetResultParam         
    rts 
    

;CURSET function - 
;   Param1: x
;   Param2: y
;   Param3: fb
;==============================================================
_u_curset
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq curset_rom1_1
    jsr _LoadThreeParams
    jmp ROM1_0_ROUTINE__CURSET      ;Jump to ROM 1.0 routine
    jsr _SetResultParam
    rts 
curset_rom1_1
    jsr _LoadThreeParams
    jmp ROM1_1_ROUTINE__CURSET      ;Jump to ROM 1.0 routine
    jsr _SetResultParam
    rts 


;CIRCLE function -
;   Param1: Radius
;   Param2: fb
;==============================================================
_u_circle
	lda VERSIONCODEADDR             ;Get Verson from ROM
	cmp #"1"                        ;Is it ROM 1.1?
	beq circle_rom1_1
    jsr _LoadTwoParams
    jmp ROM1_0_ROUTINE__CIRCLE      ;Jump to ROM 1.0 routine
    jsr _SetResultParam
    rts 
circle_rom1_1
    jsr _LoadTwoParams
    jmp ROM1_1_ROUTINE__CIRCLE      ;Jump to ROM 1.1 routine    
    jsr _SetResultParam
    rts 


;CURMOV function - 
;   Param1: x
;   Param2: y
;==============================================================
_u_curmov
    jsr _LoadTwoParams
    jmp ROM1_0_ROUTINE__CURMOV      ;Jump to ROM routine, v1.0 and v1.1 have the same entry point
    rts 


; Helper routines to load function parameters
;==============================================================

;Load a single parameter
_LoadOneParam
.(
    ldy #0         
    sty $2e0                        ;Zero error indicator.
    ldx #0                          ;Set first byte of stack
    lda (sp),y                      ;Fetch off stack
    sta $2e1                        ;Store into low byte of param block
    iny    
    lda (sp),y
    sta $2e2                        ;High byte
    rts
.)

;Load 2 parameter3
_LoadTwoParams
.(
    ldy #0         
    sty $2e0                        ;Zero error indicator.
    ldx #0                          ;Set first byte of stack
    lda (sp),y                      ;Fetch off stack
    sta $2e1                        ;Store into low byte of param block
    iny    
    lda (sp),y
    sta $2e2                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 2 from stack
    sta $2e3                        ;Low byte
    iny    
    lda (sp),y
    sta $2e4                        ;Fourth byte
    rts
.)

;Load 3 parameters
_LoadThreeParams
.(
    ldy #0         
    sty $2e0                        ;Zero error indicator.
    ldx #0                          ;Set first byte of stack
    lda (sp),y                      ;Fetch off stack
    sta $2e1                        ;Store into first low of param block
    iny    
    lda (sp),y
    sta $2e2                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 2 from stack
    sta $2e3                        ;Low byte
    iny    
    lda (sp),y
    sta $2e4                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 3 from stack
    sta $2e5                        ;Low byte
    iny    
    lda (sp),y
    sta $2e6                        ;High byte
    rts
.)

;Load 4 parameters
_LoadFourParams
.(
    ldy #0         
    sty $2e0                        ;Zero error indicator.
    ldx #0                          ;Set first byte of stack
    lda (sp),y                      ;Fetch off stack
    sta $2e1                        ;Store into low byte of param block
    iny    
    lda (sp),y
    sta $2e2                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 2 from stack
    sta $2e3                        ;Low byte
    iny    
    lda (sp),y
    sta $2e4                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 3 from stack
    sta $2e5                        ;Low byte
    iny    
    lda (sp),y
    sta $2e6                        ;High byte
    iny    
    lda (sp),y                      ;Fetch - Param 4 from stack
    sta $2e5                        ;Low byte
    iny    
    lda (sp),y
    sta $2e6                        ;High byte
    rts
.)

;Set the output of the paramer to see and non-zero errors
_SetResultParam
    lda $2e0                        ;Return error from Graphics or sound routines

