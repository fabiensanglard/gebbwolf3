#include <dos.h>
#include <stdio.h>

char far *VGA = ( char far*) 0xA0000000L ;

#define SC_INDEX 0x03c4
#define SC_DATA 0x03c5
#define CRTC_INDEX 0x03d4
#define CRTC_DATA 0x03d5
#define MEMORY_MODE 0x04
#define CRTC_UNDERLINE 0x14
#define CRTC_MODE 0x17

#define MAP_MASK 2
#define MS_PER_TICK 53
void VL_DePlaneVGA(void) {
  // Change how VRAM is written ( Disable Chain -4)
  outp ( SC_INDEX , MEMORY_MODE);
  outp ( SC_DATA , (inp ( SC_DATA ) &~8) );
  // Clear all four banks since the bios only cleared
  // the first 16K of each banks when setiing up mode 13h.

  // Change how VRAM is read by the CRTC
  // Addressing mode is selected via CRTC_MODE register .
  outp ( CRTC_INDEX , CRTC_UNDERLINE );
  outp ( CRTC_DATA , 0x00);
  // CRTC addressing mode set to byte .
  outp ( CRTC_INDEX , CRTC_MODE ) ;
  outp ( CRTC_DATA , 0xa3 ) ;

}

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

void interrupt timer(), interrupt (*old_handler)();

int ticks=0;
int multipliers = 0;
void _interrupt _far tick() {
if (++ticks == MS_PER_TICK) {
    old_handler();
    ticks = 0;
    multipliers++;
  }
outp(0x20,0x20);
}
int main(int argc, char** argv) {

	int x;
  int delta;
  int start_time;

  old_handler = getvect(8);
  setvect(8, tick);
  outportb(0x21, inportb(0x21) & 0xfe);
  outportb(0x43, 0x34);
  outportb(0x40, 0xcd); /* least significant byte of timer count */
  outportb(0x40, 0x04); /* most significant byte of timer count  */

	if(argc > 1000)
		argv[0] = argv[1];
	asm mov ax ,0x13
    asm int 0x10

    VL_DePlaneVGA();
    for(x=0;x<10;x++) {
       ClearScreen(x);
    }

	asm mov ax ,0x3
    asm int 0x10


 printf("Delta %dms/frame", (multipliers*  MS_PER_TICK + ticks)/10);
 setvect(8, old_handler);
    return 1;
}