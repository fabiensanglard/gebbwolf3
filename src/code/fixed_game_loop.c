int gameOn = 1
int simulationTime = 0;

while (gameOn){
  int realTime = Gettime();

  while (simulationTime < realTime){
         simulationTime += 28; //Timeslice is ALWAYS 28 ms. 
         UpdateWorld(28);
  }

  RenderWorld();
}	