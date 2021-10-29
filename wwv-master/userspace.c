//Blake Lufkin
//userspace code that obtains the current time from the system and
//sends that info to kernel space for encoding
//Last Updated: 4/16/2020
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
#include "wwv.h"

//Struct passed to kernelspace from userspace 
struct wwv_tm {
    int year;
    int day_of_year;
    int hour;
    int min;
};

int main(int argc, char *argv[])
{
	struct wwv_tm *userpassed; 
	struct tm *timedata;
	time_t current;
	int passfail[100];
	int monthdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int ret_val, fd, count = 0;
	int i, x;
	char DEVICE_FILE_NAME[]="/dev/wwv";

	//Allocate memory for struct
	userpassed = (struct wwv_tm *)malloc(sizeof(struct wwv_tm));
	
	for (i=0;i<30;i++) {


		if (i==28) {
			fork();
		}
		//Get current time data based on system time
		time(&current);

		//Take current time and return pointer to tm struct
		timedata = localtime(&current);

		if (timedata == NULL) {
			printf("Error retrieving date and time.\n");
			ret_val = -2;
			goto fail; 
		}
		
		userpassed->day_of_year = 0;	
	
		for(x=0;x<timedata->tm_mon;x++) {
			userpassed->day_of_year = userpassed->day_of_year + monthdays[x];
		}
		userpassed->day_of_year = userpassed->day_of_year + timedata->tm_mday;

		//Transfer data to userpassed 
		userpassed->year = timedata->tm_year +1900;
		userpassed->day_of_year = timedata->tm_yday;
		userpassed->hour = timedata->tm_hour;
		userpassed->min = timedata->tm_min; 
		
		//Check for NULL pointers and validity of data
		if (userpassed->year == NULL || userpassed->day_of_year == NULL || userpassed->hour == NULL || userpassed->min == NULL) {
			printf("There is a NULL pointer in data. Cannot pass to kernel\n");
			ret_val = -3;
			goto fail; 
		}
		if (userpassed->year > 2035 || userpassed->year < 2020) {
		    printf("Invalid year (2020 - 2035)\n");
			ret_val = -4;
			goto fail; 
		}
		if (userpassed->day_of_year < 0 || userpassed->day_of_year > 365) {
		    printf("Invalid day value (365 days in a non-leap year)\n");
			ret_val = -4;			
			goto fail; 
		}
		if (userpassed->hour < 0 || userpassed->hour > 23) {
			printf("Invalid hour value (24 hrs in a day)\n");
			ret_val = -4;
			goto fail; 
		}
		if (userpassed->min < 0 || userpassed->min > 59) {
		    printf("Invalid minute value (60 min in an hr)\n");
			ret_val = -4;
			goto fail; 
	    }
		
		//Check for function of nonblocking
		if (i==0 || i==1) {
			//Obtain file descriptor by opening the device file and check for errors
			fd = open(DEVICE_FILE_NAME,O_WRONLY | O_NONBLOCK);
			if (fd<0) {
				printf("Cant open device file: %s\n",DEVICE_FILE_NAME);
				ret_val = -5;
				goto fail; 
			}
		} else {
			//open normally without nonblocking
			fd = open(DEVICE_FILE_NAME,O_WRONLY);
			if (fd<0) {
				printf("Cant open device file: %s\n",DEVICE_FILE_NAME);
				ret_val = -5;
				goto fail;
			}
		}

		//Call ioctl and pass the buffer userpassed to the kernel	
		ret_val=ioctl(fd, WWV_TRANSMIT, userpassed);
	
		if (ret_val) {
			printf("Encoding Failed!\n");
			goto fail;
		} else {
			printf("Encoding Sucess!\n");	
		}
	
		//Free the allocated data
		passfail[count] = ret_val;
		count++;
		fail:
			passfail[count] = ret_val;
			count++;
			continue;
	}
	
	//Print all errors found in testing
	for(i=0;i<count;i++) {
		printf("%d\n",passfail[i]);
	}
	free(userpassed);
	return 0;
}
