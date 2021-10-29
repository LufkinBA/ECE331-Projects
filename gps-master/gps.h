//gps.h
#ifndef GPS_H_
#define GPS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parsedata(const char *filename, int field);	//PRE: vaild filename with GPS data,field to be highlighted
													//POST: returns an array of which lines contain 
													//the correct field to be highlighted
void highlight(char * string, int field);			//PRE: String is GPS data
													//POST: highlights selected field and prints
#endif
