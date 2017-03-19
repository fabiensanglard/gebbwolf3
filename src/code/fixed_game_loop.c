int gameOn = 1
int simulationTime = 0;

while (1){
  int realTime = Gettime();

  while (simulationTime < realTime){
         simulationTime += 14; //Timeslice is ALWAYS 14ms. 
         UpdateWorld(14);
  }

  RenderWorld();
}	