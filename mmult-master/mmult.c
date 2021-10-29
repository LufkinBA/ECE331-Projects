//Blake Lufkin
//mmult.c
//Functions to be used for matrix multiplication
//print_array function primarily used in testing results
//Last Updated: 2/23/2020

#include <stdio.h>
#include <stdlib.h>
#include "mmult.h"

//Allocates the memory for each matrix dynamically
struct matdata *allocate(int r, int c)
{	
	//Allocates the memory nessecary for the struct itself
	struct matdata *data; 
	
	//Allocates the memory nessecary for the struct itself
	data = malloc(sizeof(struct matdata));	

	data->rows = r;
	data->cols = c;

	//Allocates the memory for an array of int for r * c variables
	data->matrix = malloc(sizeof(int) * r * c);
	
	return data;
}

//Function to print out the array if desired
void print_array(struct matdata *data)
{
	int i, j = 0, r, c;
	
	r = data->rows;
	c = data->cols;

	//Where j is the counter to a new line in the matrix array 
	for (i=0;i<r * c;i++) {
		printf("%d\t",data->matrix[i]);
		j++;
		if (j==c) {
			printf("\n");
			j=0;
		}
	}
}

//Puts numbers into each element of the array
void populate(struct matdata *data)
{
	int i, j, k;

	k = data->rows;
	j = data->cols;
	
	//Assigns a sequential value to arbirarily fill the array	
	for (i=0;i<(k * j);i++) {
		data->matrix[i] = i;
	}
	
	return; 	
}

/*Function that multiplies the matricies
 *Since matrix is stored as a single array, 3 for loops are used to 
 *correctly multiply the required rows to columns.  
 */
struct matdata *mmult(struct matdata *m1, struct matdata *m2)
{
	int nc, nr, i, j, k, l = 0, t = 0;
	struct matdata *result;

	nr = m1->rows;
	nc = m2->cols;
	
	//Checking to see if you can legally multiply the two matricies
	if (m1->cols != m2->rows) {
		printf("Cannot multiply these two matricies\n");
		return NULL; 	
	}

	result = allocate(nr, nc);

	//Multiplies first row m1 by first column m2 then proceeds across the 
	//entire array
	for (i=0;i<m1->rows*m1->cols;i=i+m1->cols) {
		for (j=0;j<m2->cols;j++) {
			for (k=0;k<m1->cols;k++) {
				t=t+(m1->matrix[k+i] * m2->matrix[j+(m2->cols * k)]);
			}
			result->matrix[l] = t;
			t = 0;
			l++;
		}
	}
	return result; 
}
