	mov	eax,[bp+8]
	cdq
	idiv [DWORD PTR bp+12]
	mov	edx,eax
	shr	edx,16