//
//  main.c
//  raycaster_explainer
//
//  Created by fabien sanglard on 2014-10-02.
//  Copyright (c) 2014 memset software. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char map[64][64];


typedef struct{
    float x;
    float y;
    int angle;
    float fov;
} player_t;

player_t player;

typedef struct{
    float origX;
    float origY;
    
    float dirX;
    float dirY;
    
    float endX;
    float endY;
    
} ray_t;

static const int numRays = 40;
ray_t rays[numRays];


bool mapLoaded ;


void Init(void){
    memset(map,0,sizeof(map));
    memset(rays,0,sizeof(rays));
    player.fov = 90;
    
    mapLoaded = false;
}

bool ReadMap(const char* filename){
    
    
    
    FILE* mapFile = fopen(filename, "r");
    if (!mapFile){
        printf("Unable to open map file '%s'\n",filename);
        return false;
    }
    
    int posX,posY;
    char type;
    while (fscanf(mapFile,"%d %d %c",&posX,&posY,&type) != EOF) {
        map[posX][posY] = type;
    }
    
    fclose(mapFile);
    
    return true;
}

//Write endX and endY
void traceRay(ray_t* ray){
    
    //which box of the map we're in
    int mapX = int(ray->origX);
    int mapY = int(ray->origY);
    
    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;
    
    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = sqrt(1 + (ray->dirY * ray->dirY) / (ray->dirX * ray->dirX));
    double deltaDistY = sqrt(1 + (ray->dirX * ray->dirX) / (ray->dirY * ray->dirY));
    
    
    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;
    
    int hit = 0; //was there a wall hit?
    int side =0; //was a NS or a EW wall hit?
    
    
    //calculate step and initial sideDist
    if (ray->dirX < 0)
    {
        stepX = -1;
        sideDistX = (ray->origX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - ray->origX) * deltaDistX;
    }
    if (ray->dirY < 0)
    {
        stepY = -1;
        sideDistY = (ray->origY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - ray->origY) * deltaDistY;
    }
    
    //perform DDA
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        //Check if ray has hit a wall
        if (map[mapX][mapY] > 0) hit = 1;
    }
    
    float a = (ray->dirY-ray->origY)/(ray->dirX-ray->origX);
    float b = 0;
    
    if (side == 0){
        ray->endX = mapX;
        ray->endY = a*mapX + b;
    }
    else{
        if (a==0) a =1 ;
        ray->endX = (mapY-b)/a;
        ray->endY = mapY;
    }
    
    
    
}

void RayCastAll(){
    
    float angleStep = player.fov / numRays;
    float startAngle = - player.fov / 2 ;
    
    ray_t *ray = rays;
    for (int i=0 ; i < numRays; i++,ray++) {
        ray->origX = player.x;
        ray->origY = player.y;
        
        float angle = player.angle + startAngle + angleStep * i ;
        
        ray->dirX = cosf(angle*2*3.1415/360.0f);
        ray->dirY = sinf(angle*2*3.1415/360.0f);
        
        traceRay(ray);
    }
}

void GenerateTIKZCommands(const char* filename){
    FILE* outputFile = NULL ;
    
    outputFile = fopen(filename,"w");
    
    //Write prolog
    fprintf(outputFile,"\\documentclass{standalone}\n\\usepackage{tikz}\n\\begin{document}\n\\begin{tikzpicture}[y=-1cm]");
    
    //Generate map
    for (int x = 0 ; x < 64 ; x++)
        for (int y = 0 ; y < 64 ; y++){
            if (map[x][y]){
                fprintf(outputFile,"\\draw (%d,%d) rectangle (%d,%d) node[pos=.5] {%c};\n",x,y,x+1,y+1,map[x][y]);
            }
        }
    
    //Generate rays
    ray_t* ray = rays;
    for (int i=0 ; i < numRays; i++,ray++) {
        fprintf(outputFile,"\\draw[thin,black] (%f,%f) -- (%f,%f);\n",ray->origX,ray->origY,ray->endX,ray->endY);
    }
    
    //Write epilog
    fprintf(outputFile,"\\end{tikzpicture}\n\\end{document}");
    
    fclose(outputFile);
}

const char* GenerateTIKZFilename(const char* mapFilename){
    static char name[512];
    
    char* cursor = name;
    
    while (*mapFilename && *mapFilename != '.') {
        *cursor++ = *mapFilename++;
    }
    
    *cursor++ = '.';
    *cursor++ = 't';
    *cursor++ = 'e';
    *cursor++ = 'x';
    
    
    return name;
}

const char* mapFilename = NULL;

void ReadParameters(int argc, const char* argv[]){
    mapFilename = argv[1] ;
    float playerPositionX = atof(argv[2]);
    float playerPositionY = atof(argv[3]);
    int playerAngle = atoi(argv[4]);
    
    mapLoaded = ReadMap(mapFilename);
    player.x = playerPositionX;
    player.y = playerPositionY;
    player.angle = playerAngle;

}

int myargc = 5 ;
const char* myargv[] ={
     "raycaster_explayner",
     "beginning.map",
     "29.5",
     "57.5",
     "0"
};

int main(int argc, const char * argv[]) {
    
    Init();
    
    ReadParameters(myargc,myargv);
    
    if (!mapLoaded)
        return EXIT_FAILURE;
    
    RayCastAll();
    
    const char* outputName = GenerateTIKZFilename(mapFilename);
    
    GenerateTIKZCommands(outputName);
    
    return EXIT_SUCCESS;
    
}
