//Blake Lufkin
//main.c
//implements the mmult() function by taking in 4 arguments when run
//allocates the memory to be used in the process then populates the 
//matrix with incremental values and multiplies the two matricies while
//timing the entire process to discern the total time taken. 
//Last updated: 2/23/20

#include <stdio.h>
#include <stdlib.h>
#include "mmult.h"
#include <time.h>


int main (int argc, char *argv[])
{
	int r1, c1, r2, c2; 
//	char print; //uncomment to use print function
	struct matdata *m1;
	struct matdata *m2;
	struct matdata *result; 
	struct timespec begin, end;
	double timetaken; 

	//convert passed arguments to int values	
	r1 = atoi(argv[1]);
	c1 = atoi(argv[2]);
	r2 = atoi(argv[3]);
	c2 = atoi(argv[4]);
	
	//dynamically allocate resources
	m1 = allocate(r1, c1);
	m2 = allocate(r2, c2);

	//fill the matricies 
	populate(m1);
	populate(m2);
	
	//Timestamp before mmult	
	clock_gettime(CLOCK_REALTIME, &begin);

	//Perform the matrix multiplication
	result = mmult(m1, m2);
	
	//Timestamp after mmult
	clock_gettime(CLOCK_REALTIME, &end);
	
	//Calculates the time taken in seconds
	timetaken =(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec)/1000000000.0;
	printf("Total time taken: %f seconds\n", timetaken);
	
	//Optional Print loop. excluded for final submit	
/*	while (print != 'Y' && print != 'N') {
		printf("Print out result of the multiplication?(Y/N)\n");
		scanf("%c", &print);
			
			if (print != 'Y' && print != 'N') {
				printf("Type Y or N\n");
			} else if(print == 'Y') {
				print_array(result);
			}
	} 
*/
	//Free dynamically allocated memory
    if (result == NULL) {
		free(result);
	} else {
		free(result->matrix);
		free(result);
	}
    //Freed regardless of result return value
	free(m1->matrix);
    free(m1);
    free(m2->matrix);
    free(m2);

	return 0; 
}
