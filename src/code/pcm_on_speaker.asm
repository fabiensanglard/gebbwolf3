PROC    SDL_t0ExtremeAsmService
PUBLIC  SDL_t0ExtremeAsmService

    ... 

    les	di,[pcSound]       ; Prepare to get byte.
    mov	ax,es
    or	ax,di
    jz	@@donereg          ; nil pointer

    mov	bl,[es:di]         ; Get the PCM byte
    inc	[WORD PTR pcSound] ; Increment pointer

    and	bl,11100000b       ; Nuke some of the precision 
                           ; (DEBUG: do this with table)
    xor	bh,bh
    mov	ah,[pcdtab+bx]     ; Translate the byte
                             
    in	al,pcSpeaker
    and	al,11111100b
    or	al,ah
    out	pcSpeaker,al