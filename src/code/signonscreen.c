// Content of GAMEPAL.OBJ:
// accoumt for 256 * 3 = 768 bytes.
extern byte far gamepal;   

// Content of SIGNON.OBJ:
// accounts for 320x200 = 64,000 bytes.
extern char	far introscn;  

void SignonScreen (void)
{
  unsigned  segstart,seglength;

  VL_SetVGAPlaneMode ();
  VL_TestPaletteSet ();
  VL_SetPalette (&gamepal);

  if (!virtualreality)
  {
    VW_SetScreen(0x8000,0);
    VL_MungePic (&introscn,320,200);
    VL_MemToScreen (&introscn,320,200,0,0);
    VW_SetScreen(0,0);
  }

  // reclaim the memory from the linked signon screen
  segstart = FP_SEG(&introscn);
  seglength = 64000/16;
  if (FP_OFF(&introscn)){
    segstart++;
    seglength--;
  }
  MML_UseSpace (segstart,seglength);
}