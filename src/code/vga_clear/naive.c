byte far *VGA = (byte far*)0xA0000000L; 
char color = 0;

for (int x = 0 ; x < 320 ; x++) {
	for (int y=0 ; y < 200 ; y++) {
	  /* select plane */
       outp(SC_INDEX, MAP_MASK);
       outp(SC_DATA,  1 << (x&3) );

       VGA[(y<<8)+(y<<6)+x]=color;
	}
}

