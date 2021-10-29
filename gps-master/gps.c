//gps.c
#include "gps.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**void parsedata()-opens a file and reads lines individually
 * const char *filename: the string that holds the name of
 * the file to be opened and scanned from
 * int field: the field in between two commas that the user
 * wishes to highlight in the output
 *
 * parsedata opens a file and scans line by line, passing
 * each line as a string to function highlight()
 *
 * No return value 
 */
void parsedata(const char *filename, int field)
{
FILE *data=fopen(filename, "r");
int i=0, lineerror=0;
char stuff[2000];
while (fscanf(data,"%s",stuff) ==1) {		
	if (stuff[0]!='$') 
		lineerror++;		
	i++;
	highlight(stuff, field);
}
printf("\n%d lines have errors\n",lineerror);
printf("\n%d lines of data processed\n",i);
return; 
}

/*void highlight()- takes a string and the selected field and highlights it
 * on the output by printing character by character
 * 
 * char *string: a pointer to a string presumably of GPS data
 * int field: see above explination in parsedata
 *
 * highlight() looks through the entire string once, determines the position
 * that needs to be highlighted by the comma positions and prints each character
 * individually 
 *
 * No return value
 */
void highlight(char *string, int field) 
{
int size, firstc, secondc, i, commacount=0;
const char comma=',';

size=strlen(string);
firstc=field-1;
secondc=field;

for (i=0;i<size;i++) {	
	if (string[i]==comma)
		commacount++;
}

if (commacount<firstc)	
	return;

commacount=0;	
for (i=0;i<size;i++) {
	
	if (commacount<firstc)	
		printf("%c",string[i]);
	
	if (commacount==firstc)	{
		if (string[i]==comma) {
			printf("%c",string[i]);
		} else {
			printf("\033[0;36m");		
			printf("%c",string[i]);
			printf("\033[0m");
		}
	}
	
	if (commacount>=secondc)
		printf("%c",string[i]);		

	if (string[i]==',')
		commacount++;
}
printf("\n");
return; 
}
