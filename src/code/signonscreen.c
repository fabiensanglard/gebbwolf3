extern byte far gamepal; // content of GAMEPAL.OBJ
extern char	far introscn;  // content of SIGNON.OBJ

void SignonScreen (void) // VGA version
{
  unsigned  segstart,seglength;

  VL_SetVGAPlaneMode ();
  VL_TestPaletteSet ();
  VL_SetPalette (&gamepal);

  VW_SetScreen(0x8000,0);
  VL_MungePic (&introscn,320,200);
  VL_MemToScreen (&introscn,320,200,0,0);
  VW_SetScreen(0,0);

  // reclaim the memory from the linked in signon screen
  segstart = FP_SEG(&introscn);
  seglength = 64000/16;
  if (FP_OFF(&introscn)){
    segstart++;
    seglength--;
  }
  MML_UseSpace (segstart,seglength);
}