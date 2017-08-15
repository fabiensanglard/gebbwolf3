#include "common.c"

void ClearScreen(char color) {
	int* vga ;
	int y, x;
	int wide_color = color << 8 || color;

    vga = = (int*)VGA;
    outp ( SC_INDEX , MAP_MASK ) ;
	outp ( SC_DATA , 15) ;
     
	for ( x = 0 ; x < 80 ; x++) {
		for ( y = 0 ; y < 200 ; y++) {
		vga [(y << 6) + (y << 4) + ((x*4) >> 2)]= wide_color ; // y *40 + x
		}
	}
}