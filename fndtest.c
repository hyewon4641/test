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


static pthread_t colorled_id;

void colorled_OnOff(void* Arg)
{
	pwmSetPercent(atoi("100"),0);
	pwmSetPercent(atoi("0"),1);
	pwmSetPercent(atoi("0"),2);
	usleep(500*1000);
	
	pwmSetPercent(atoi("0"),0);
	pwmSetPercent(atoi("0"),1);
	pwmSetPercent(atoi("0"),2);
	usleep(500*1000);
}

int main(void)
{
	ledLibInit();
	int i;
	for(i=60;i>=0;i--)
	{
		fndDisp(i,0);
		
		if(i==10)
		{
			pthread_create(&colorled_id,NULL,&colorled_OnOff,NULL);			
		}
		
		for(i=10;i>=0;i--)
		{
			fndDisp(i,0);
		}
		 pthread_exit()
	 }
			
	sleep(1);
	
}
	ledLibExit();

}
	



