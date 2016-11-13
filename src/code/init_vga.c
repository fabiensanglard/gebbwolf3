void	VL_SetVGAPlaneMode (void) {
  // Call 17th interrupt vector with value 0x13
  asm	mov	ax,0x13
  asm	int	0x10

  VL_DePlaneVGA ();
  VGAMAPMASK(15);
  VL_SetLineWidth (40);
}