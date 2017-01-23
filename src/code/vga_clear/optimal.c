word far *VGA = (word far*)0xA0000000L; 
word color = 0x0000;

/* select all planes */
outp(SC_INDEX, MAP_MASK);
outp(SC_DATA, 15);

for (int y=0 ; y < 200 ; y++) {
    for (int x = 0 ; x < 40 ; x++) {	
        VGA[(y<<3)+(y<<5)+x]=color;  // y*40 + x
	}
}
