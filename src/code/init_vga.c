void	VL_SetVGAPlaneMode (void) {
  // Call 17th interrupt vector with value 0x13
  // (Ask the BIOS to to setup the VGA in mode 13h)
  asm	mov	ax,0x13
  asm	int	0x10

  // Unchain (called deplane in the engine)
  VL_DePlaneVGA ();
  VGAMAPMASK(15);
  VL_SetLineWidth (40);
}