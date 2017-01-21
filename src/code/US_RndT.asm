;=================================================
;
; int US_RndT (void)
; Return a random # between 0-255
; Exit : AX = value
;
;=================================================
PROC	US_RndT
	public	US_RndT

	mov	ax,SEG rndtable
	mov	es,ax
	mov	bx,[es:rndindex]
	inc	bx
	and	bx,0ffh
	mov	[es:rndindex],bx
	mov	al,[es:rndtable+BX]
	xor	ah,ah
	ret

ENDP