mov ax,0x13 ; AH=0 (Change video mode), AL=13h (Mode)
int 0x10.   ; Video BIOS interrupt
