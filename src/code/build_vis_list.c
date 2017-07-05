#define MAXVISABLE	50

typedef struct {
	int	viewx,viewheight,shapenum;
} visobj_t;

visobj_t	vislist[MAXVISABLE],*visptr,*visstep,*farthest;

void DrawScaleds (void) {
	int numvisable=0;
	visptr = &vislist[0];

	// Use spotvis[] to add objects to visptr. Increase numvisable

    // draw from back to front
	for (i = 0; i<numvisable; i++){
		least = 32000;
		for (visstep=&vislist[0] ; visstep<visptr ; visstep++){
			height = visstep->viewheight;
			if (height < least){
				least = height;
				farthest = visstep;
			}
		}
		ScaleShape(farthest->x,farthest->id,farthest->height); 
		farthest->viewheight = 32000;
	}

}