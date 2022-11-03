void CheckKeys (void) {
  if (Paused) {
    LatchDrawPic (20-4,80-2*8,PAUSEDPIC);
    ...
  }
}    


void PreloadGraphics(void) {
	LatchDrawPic (20-14,80-3*8,GETPSYCHEDPIC);
	...
}