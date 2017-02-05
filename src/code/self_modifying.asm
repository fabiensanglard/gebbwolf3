asm	mov	bx,[ds:bp]        ; table location of rtl to patch
asm	or	bx,bx
asm	jz	linedone          ; 0 signals end of segment list
asm	mov	bx,[es:bx]
asm	mov	dl,[es:bx]        ; save old value
asm	mov	BYTE PTR es:[bx],OP_RETF    ; patch a RETF in
asm	mov	si,[ds:bp+4]      ; table location of entry spot
asm	mov	ax,[es:si]
asm	mov	WORD PTR ss:[linescale],ax  ; call here to start scaling
asm	mov	si,[ds:bp+2]      ; corrected top of shape for this segment
asm	add	bp,6              ; next segment list

asm	mov	ax,SCREENSEG
asm	mov	es,ax
asm	call ss:[linescale]   ; scale the segment of pixels

asm	mov	es,cx             ; segment of scaler
asm	mov	BYTE PTR es:[bx],dl	; unpatch the RETF
asm	jmp	scalesingle       ; do the next segment