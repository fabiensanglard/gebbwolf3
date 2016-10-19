for (int x=0 ; x< 320 ; x++) {
  castRay();
  height = CalculateWallHeight();
  drawColumn(x, height);
}
