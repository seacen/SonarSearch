/* 
 COMP20007 Design of Algorithms 

 Read in an estimate (upper bound) of terrain heights (2D in row-major
 form), the actual terrain heights, a list of locations to visit in order, and 
 then traverse the actual grid in the order given recording actual heights.

 Write output to input file name with extension .bit.

 Also compute the battery use by the robot and print it to stdout.

 Author: Andrew Turpin (aturpin@unimelb.edu.au)
 Date: May 2014

 Usage: see usage()
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "grid.h"
#include "bitfile.h"



#define MOVES_PER_BATTERY   25
#define FILE_NAME_LEN        7
#define FORMAT_LEN           4
#define MAX_READING_LEN      4
#define NEW_LINE_CHR_LEN     1
#define BIN_CHOICES         10
#define CODE_LEN_INTERVAL    3
#define CODE_LEN_CEILING    10
#define SMALL_LEN            0
#define BIG_LEN              1

/****************************************************************************/
int bit_len(int value);
/****************************************************************************/


/*
** Print usage message
*/
void
usage(char *exeName) { 
    fprintf(stderr,"Usage: %s estimateFileName actualFileName plotterFileName\n",exeName);
}

/*
** Read command line params, call search
*/
int 
main(int argc, char *argv[]) {
	int i,flag=1,len,width,height,diff;
	uint32_t bits_sent=0, moves_made=0;

    if (argc != 4) {
        usage(argv[0]);
        return(-1);
    }

        // plotter is not really a "grid" but why not use the read routine
        // to save coding!
    grid_t *sonar   = readGrid(strcmp(argv[1],"-")?fopen(argv[1],"r"):stdin, TRUE);
    grid_t *actual  = readGrid(strcmp(argv[2],"-")?fopen(argv[2],"r"):stdin, TRUE);
    grid_t *plotter = readGrid(strcmp(argv[3],"-")?fopen(argv[3],"r"):stdin, FALSE);

    assert(sonar);
    assert(actual);
    assert(plotter);

        // create output file
    char output_file_name[FILE_NAME_LEN+FORMAT_LEN+1];
    sprintf(output_file_name,"%s.bit",argv[2]);
    bit_file_t *bitfile = BitFileOpen(output_file_name, BF_WRITE);
    assert(bitfile);  
	
    width=(int)plotter->width;
    height=(int)plotter->height;
    
    data_t current_position = plotter->data[0];
    for(i=0;i<width*height;i++) {
        data_t new_position = plotter->data[i];
        moves_made += gridDistance(plotter, current_position, new_position);
        current_position = new_position;
        
    	diff=int((sonar->data[current_position])-(actual->data[current_position]));
    	if (current_position==261632) {
    		printf("%d\n",diff);
    		printf("%d\n",(sonar->data[current_position]));
    		printf("%d\n",(actual->data[current_position]));
    	}
    	if ((bit_len(diff))<=CODE_LEN_INTERVAL) {
            flag=SMALL_LEN;
            len=CODE_LEN_INTERVAL;
        }
        else {
            flag=BIG_LEN;
            len=CODE_LEN_CEILING;
        }
        bits_sent+=(len+1);
        BitFilePutBit(flag,bitfile);
        BitFilePutBitsInt(bitfile,&diff,len,sizeof(diff));
    }

    printf("M: %10d B: %10d Bat: %10.1f\n",
        moves_made, bits_sent, 
        (float)moves_made/(float)MOVES_PER_BATTERY + (float)bits_sent);

    return 0;
}

/****************************************************************************/

int bit_len(int value) {
	int binary[BIN_CHOICES];
	int i,max_bin=512,len=0;
	
	for (i=0;i<BIN_CHOICES;i++) {
		binary[i]=max_bin;
		max_bin/=2;
	}
	
	for (i=0;i<BIN_CHOICES;i++) {
		if ((value-binary[i])>=0) {
			len=10-i;
			break;
		}
	}
	return len;
}

