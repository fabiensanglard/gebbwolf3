boolean FizzleFade {
	long rndval = 1;
	int x,y;
	do{
		// seperate random value into x/y pair
		asm	mov	ax,[WORD PTR rndval]
		asm	mov	dx,[WORD PTR rndval+2]
		asm	mov	bx,ax
		asm	dec	bl
		asm	mov	[BYTE PTR y],bl			// low 8 bits - 1 = y
		asm	mov	bx,ax
		asm	mov	cx,dx
		asm	mov	[BYTE PTR x],ah			// next 9 bits = x
		asm	mov	[BYTE PTR x+1],dl
		
		// advance to next random element
		asm	shr	dx,1
		asm	rcr	ax,1
		asm	jnc	noxor
		asm	xor	dx,0x0001
		asm	xor	ax,0x2000
noxor:
		asm	mov	[WORD PTR rndval],ax
		asm	mov	[WORD PTR rndval+2],dx

		if (x>width || y>height) continue;

		copy_screen_pixel(x,y);

		if (rndval == 1) return false; // end sequence
		
	} while (1)
}
