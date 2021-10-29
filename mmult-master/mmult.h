//Blake Lufkin
//mmult.h
//Header file/prototypes for all functions used in mmult
//Last updated: 2/23/2020

#ifndef MMULT_H
#define MMULT_H
#include <stdio.h>
#include <stdlib.h>

//Stores the data required for matrix multiplication
struct matdata
{
	int rows;
	int cols;
	int* matrix;
};

//Allocates the memory for each matrix dynamically
struct matdata *allocate(int r, int c);

//Function to print out the array if desired
void print_array(struct matdata *data);

//Gets passed two matricies to be multiplied together
//Spits null pointer and error message if incompatible types
struct matdata *mmult(struct matdata *m1, struct matdata *m2);

//puts numbers into each element of the array
void populate(struct matdata *data);

#endif
