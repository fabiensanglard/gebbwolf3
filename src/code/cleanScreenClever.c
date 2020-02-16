void CleanScreen(int color) {
  for(int x=0; x < 320 ; x++) {
    selectPlane(x % 4);
    for(int y=0 ; y < 200 ; y++) {
      writePixel(x, y, color);   
    }
  }
}