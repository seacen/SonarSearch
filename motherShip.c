/* 
 COMP20007 Design of Algorithms 

 Read in an estimate (upper bound) of terrain heights (2D in row-major
 form), a list of locations to visit in order, and the bitfile.
 Output the actual heights to stdout.

 Author: Andrew Turpin (aturpin@unimelb.edu.au)
 Date: April 2014

 Usage: see usage()

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "grid.h"
#include "bitfile.h"


#define SMALL_LEN            0
#define BIG_LEN              1
#define CODE_LEN_INTERVAL    3
#define CODE_LEN_CEILING    10

/*
** Print usage message
*/
void
usage(char *exeName) { 
    fprintf(stderr,"Usage: %s sonarFileName plotterFileName bitFileName\n",exeName);
}

/*
** Read command line params, call search
*/
int 
main(int argc, char *argv[]) {
    uint32_t pos = 0;
    int flag,len,res,temp=0;
    if (argc != 4) {
        usage(argv[0]);
        return(-1);
    }

    grid_t *sonar   = readGrid(strcmp(argv[1],"-")?fopen(argv[1],"r"):stdin, TRUE);
    grid_t *plotter = readGrid(strcmp(argv[2],"-")?fopen(argv[2],"r"):stdin, FALSE);

    bit_file_t *bitfile = BitFileOpen(argv[3], BF_READ);

    assert(sonar);
    assert(plotter);
    assert(bitfile);

        // temporary home for terrain heights
    data_t *result = (data_t *)malloc(sizeof(data_t) * plotter->width * plotter->height); 
    assert(result);

    for(pos = 0 ; pos < plotter->width * plotter->height ; pos++) {
    	if((flag=BitFileGetBit(bitfile))==SMALL_LEN) {
    	    len=CODE_LEN_INTERVAL;
    	}
    	else {
            len=CODE_LEN_CEILING;
        }
        temp = 0;
        res = BitFileGetBitsInt(bitfile, &temp,len,sizeof(temp));
        if (plotter->data[pos]==261632) {
        	printf("%d\n",temp);
        }
        temp=uint32_t(temp);
        temp=sonar->data[plotter->data[pos]]-temp;
        if (plotter->data[pos]==261632) {
        	printf("%d\n",temp);
        }
        result[plotter->data[pos]] = uint32_t(temp);
        if (plotter->data[pos]==261632) {
        	printf("%d",result[plotter->data[pos]]);
        }
    }

    assert(!BitFileClose(bitfile));

    /*printf("%d %d\n", plotter->width, plotter->height);
    for(uint32_t pos = 0 ; pos < plotter->width * plotter->height ; pos++)
        printf("%d\n",result[pos]);*/

    free(result);

    return 0;
}
