for (int x=0; x<320 ; x++){
  castRay();
  if (raySimilarToOnesInBuffer){
      AddColumnToBuffer();
    continue;
  } else {
      DrawBuffer();
      height = CalcWallHeight();
      AddColumnToBuffer();
  }
}
