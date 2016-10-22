byte far *VGA = (byte far*)0xA0000000L; 
char color = 0;

/* select all planes */
outp(SC_INDEX, MAP_MASK);
outp(SC_DATA, 15);

for (int y=0 ; y < 200 ; y++) {
    for (int x = 0 ; x < 80 ; x++) {	
       VGA[(y<<4)+(y<<6)+x]=color;
	}
}
