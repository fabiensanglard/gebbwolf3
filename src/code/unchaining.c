#define SC_INDEX       0x03c4
#define SC_DATA        0x03c5

#define CRTC_INDEX     0x03d4
#define CRTC_DATA      0x03d5

#define MEMORY_MODE    0x04
#define CRTC_UNDERLINE 0x14
#define CRTC_MODE      0x17

void VL_DePlaneVGA() {  
  // Change how VRAM is written (Disable Chain-4)
  outp(SC_INDEX, MEMORY_MODE);
  outp(SC_DATA, (inp(SC_DATA)&~8)); 

  // Clear all four banks since the bios only cleared 
  // the first 16K of each banks when setting up mode 13h.
  VL_ClearVideo (0);

  // Change how VRAM is read by the CRTC
  // Addressing mode is selected via CRTC_MODE register.
  outp(CRTC_INDEX, CRTC_UNDERLINE);
  outp(CRTC_DATA, 0x00);
  // CRTC addressing mode set to byte.
  outp(CRTC_INDEX, CRTC_MODE);
  outp(CRTC_DATA, 0xa3);
}