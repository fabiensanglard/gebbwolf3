void	near ScalePost (void)           // VGA version
{
    ...	
	// scale a byte wide strip of wall
	asm	mov	bx,[postx]                  // posx = x coordinate..
	asm	mov	di,bx                       // . where to draw
	asm	shr	di,2                        // X in bytes
	asm	add	di,[bufferofs]

	asm	and	bx,3
	asm	shl	bx,3                        // bx = pixel*8+postwidth
	asm	add	bx,[postwidth]

    // First pass.
	asm	mov	al,BYTE PTR [mapmasks1-1+bx]
	asm	mov	dx,SC_INDEX+1
	asm	out	dx,al                       // set VGA bank mask 
	asm	lds	si,DWORD PTR [postsource]
	asm	call DWORD PTR [bp]             // call compiled scaler

	// Second pass.
	asm	mov	al,BYTE PTR [ss:mapmasks2-1+bx] /
	asm	or	al,al
	asm	jz	nomore
	asm	inc	di
	asm	out	dx,al                       // set VGA bank mask
	asm	call DWORD PTR [bp]             // call compiled scaler
    ...
    // Third pass.
nomore:
}