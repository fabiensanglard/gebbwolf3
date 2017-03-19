#define MAXVISABLE	50

typedef struct {
	int	viewx,viewheight,shapenum;
} visobj_t;

visobj_t	vislist[MAXVISABLE],*visptr,*visstep,*farthest;

void DrawScaleds (void) {
	int numvisable=0;
	visptr = &vislist[0];

	// Add all static object to visptr, increase numvisable
	// Add all moving object to visptr, increase numvisable

    // O(n^2) loop
	for (i = 0; i<numvisable; i++){
		least = 32000;
		for (visstep=&vislist[0] ; visstep<visptr ; visstep++){
			height = visstep->viewheight;
			if (height < least){
				least = height;
				farthest = visstep;
			}
		}
		ScaleShape(farthest->viewx,farthest->shapenum,farthest->viewheight);
		farthest->viewheight = 32000;
	}

}