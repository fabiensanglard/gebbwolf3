void CleanScreen(y, color) {
  for(int y=0 ; y < 200 ; y++) {
    for(int x=0; x < 320 ; x++) {
      selectPlan(x % 4);
      writePixel(x, y, color);   
    }
  }
}