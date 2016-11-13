#define SC_INDEX      0x03c4
#define SC_DATA       0x03c5

#define CRTC_INDEX    0x03d4
#define CRTC_DATA     0x03d5

#define MEMORY_MODE   0x04
#define CRTC_UNDERLINE 0x14
#define CRTC_MODE  0x17

void VL_DePlaneVGA() {  
  // Make sure the mode bit 4 is at 0.
  outp(SC_INDEX, MEMORY_MODE);
  outp(SC_DATA, inp(SC_DATA)&~8)); 

  // Clear all four banks since the bios
  // only cleared bank 0 when setup in 13h
  VL_ClearVideo (0);

  // turn off long mode
  outp(CRTC_INDEX, CRTC_UNDERLINE);
  outp(CRTC_DATA, 0x00);
  // turn on byte mode 
  outp(CRTC_INDEX, CRTC_MODE);
  outp(CRTC_DATA, 0xa3);
}