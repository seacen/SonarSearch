/* 
 COMP20007 Design of Algorithms 

 Read in an estimate (upper bound) of terrain heights (2D in row-major
 form), formulate a traversal strategy, and then write out the 
 position numbers in order of the traversal.

 Author: Andrew Turpin (aturpin@unimelb.edu.au)
 Date: May 2014

 Usage: see usage()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "grid.h"

typedef struct square {
	int index;   /* index in grid_t */
	int height;  /* sea level height at this square */
} square_t;

int cmpfunc (const void * a, const void * b);
/*
** Print usage message
*/
void
usage(char *exeName) { 
    fprintf(stderr,"Usage: %s sonarFileName\n",exeName);
}

/*
** Read command line params, call search
*/
int 
main(int argc, char *argv[]) {
	square_t *grid_sort;
	int height,width,h=1,i=0,plus=1,dir=0;
	
	if (argc != 2) {
		usage(argv[0]);
		return(-1);
	}
	grid_t *sonar = readGrid(strcmp(argv[1],"-")?fopen(argv[1],"r"):stdin, TRUE);
	assert(sonar);
	printf("%d %d\n", sonar->width, sonar->height);
	height=(int)sonar->height;
	width=(int)sonar->width;
	/*grid_sort=(square_t*)malloc(sizeof(*grid_sort)*width*height);
	for (i=0;i<width*height;i++) {
		grid_sort[i].height=sonar->data[i];
		grid_sort[i].index=i;
	}
	qsort(grid_sort,width*height,sizeof(*grid_sort),cmpfunc);
	for (i=0;i<width*height;i++) {
		printf("%d\n",grid_sort[i].index);
	}
	*/
	i=0;
	while (h<=height) {
		printf("%d\n",i);
		dir++;
		if (!(dir%width)) {
			i+=width;
			plus*=-1;
			h++;
		}
		else {
			i+=plus;
		}
	}
	
	
	return 0;
}

int cmpfunc (const void * a, const void * b){
	return ( ((square_t*)a)->height - ((square_t*)b)->height );
}
