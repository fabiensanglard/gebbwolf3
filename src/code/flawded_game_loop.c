int lastTime = Timer_Gettime();

while (1){
  int currentTime = Timer_Gettime();
  int timeSlice = currentTime - lastTime ;

  UpdateWorld(timeSlice);
  RenderWorld();

  lastTime = currentTime;
}