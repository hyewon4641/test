#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"
#include "colorledtest.h"

int i;

static pthread_t colorled_id;

void colorled_OnOff(void* Arg)
{
	pwmLedInit();
	while(1)
	{
	colorled_on();
	usleep(500*1000);
	
	colorled_off();
	usleep(500*1000);
	
	if(i==0)
	break;
	
}
	pwmInactiveAll();
	
	pthread_exit();
}


int main(void)
{
	
	for(i=60;i>=0;i--)
	{
		fndDisp(i,0);
		
		
		if(i==10)
		{
			int err=pthread_create(&colorled_id,NULL,&colorled_OnOff,NULL);	
			if(err==0)
			printf("ss\n");		
		}
		
			sleep(1);
		 } 
			

	pthread_exit(&colorled_id);
	
}

	



