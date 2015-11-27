#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *argv[]) {
	int *binary;
	int i;
	binary=[512,256,128,64,32,16,8,4,2,1];
	for (i=0;i<10;i++) {
		printf("%d\n",binary[i]);
	}
	
	return 0;
}
