void DrawLine(y, color) {
  for(int x=0; x < 320 ; x++) {
    SelectBank(x % 4);
    WritePixel(x, y, color);   
  }
}