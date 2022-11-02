asm mov	ax,ds 
asm mov es,ax
asm mov di,OFFSET spotvis // Array to clear
asm xor ax,ax   // Put 0 in ax
asm mov cx,2048	// repeat next instruction 64*64/2
asm rep stosw   // store ax at es:di 
