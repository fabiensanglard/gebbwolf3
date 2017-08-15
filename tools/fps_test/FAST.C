#include "common.c"

void ClearScreen(char color) {
	int y, x;

	for ( x = 0 ; x < 320 ; x++) {

	    outp ( SC_INDEX , MAP_MASK ) ;
	    outp ( SC_DATA , 1 << (x % 4)) ;
		for ( y = 0 ; y < 200 ; y++) {
		VGA [(y << 6) + (y << 4) + (x >> 2)]= color ; // y *40 + x
		}
	}
}