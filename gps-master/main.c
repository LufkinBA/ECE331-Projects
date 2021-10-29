/* Blake Lufkin main.c
 * Highlights the selected field of gps data file that it is passed. 
 * Run in command line by passing arguments in the format ./gps file field
 * where file is a gps data file and field is a positive number
 * Last updated 2/10/2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gps.h"
/* Assumes that the arguments passed will be in the format:
 * ./gps fileofdata highlightfield
 * ex: ./gps fileofdata.txt 3
 */
int main(int argc, char *argv[])
{

int field;
char *file= argv[1];

field=atoi(argv[2]);

if (field<0) {
	printf("Invalid field selection\n");
} else {
	parsedata(file,field);
}

return 0; 

}
