void CleanScreen(y, color) {
  for(int x=0; x < 320 ; x++) {
    selectPlan(x % 4);
    for(int y=0 ; y < 200 ; y++) {
      writePixel(x, y, color);   
    }
  }
}