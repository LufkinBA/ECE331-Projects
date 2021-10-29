//Blake Lufkin
//test-mmult
//implements the mmult() function
#include <stdio.h>
#include <stdlib.h>
#include "mmult.h"

int main (int argc, char *argv[])
{   
       
    struct matdata *m1;
    struct matdata *m2;
    struct matdata *result;

	m1 = allocate(1000, 1000);
	m2 = allocate(1000, 1000);

	printf("Array 1 is size: %d by %d\n", m1->rows, m1->cols);
    printf("Array 2 is size: %d by %d\n", m2->rows, m2->cols);
	printf("before populate\n");
	populate(m1);
	populate(m2);
	printf("After populate\n");
	
	result = mmult(m1,m2);

	/*print_array(m1);
	printf("\n");
	print_array(m2);
    printf("\n");
	print_array(result);
    printf("\n");*/
	
	free(result->matrix);
	free(result);
	free(m1->matrix);
	free(m1);
	free(m2->matrix);
	free(m2);
	return 0;
}

