void VL_SetPalette (byte far *palette) {
  asm mov dx,PEL_WRITE_ADR
  asm mov al,0
  asm out dx,al
  asm mov dx,PEL_DATA
  asm lds si,[palette]

  asm test  [ss:fastpalette],1
  asm jz  slowset
// set palette fast for cards that can take it
  asm mov cx,768
  asm rep outsb
  asm jmp done

// set palette slowly for some video cards
slowset:
  asm mov cx,256
setloop:
  asm lodsb
  asm out dx,al
  asm lodsb
  asm out dx,al
  asm lodsb
  asm out dx,al
  asm loop  setloop

done:
  asm mov ax,ss
  asm mov ds,ax

}