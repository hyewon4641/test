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
#include "led.h"	


static pthread_t ledTh_id;

void ledThFunc(void* Arg)
{
	int j=0;
	for(j=0;j<5;j++)
	{
	ledOnOff(6,1);
	sleep(0.5);
	ledOnOff(6,0);
	sleep(0.5);
	}
}

int main(void)
{
	ledLibInit();
	int i;
	for(i=60;i>=0;i--)
	{
		fndDisp(i,0);
		
		if(i==5)
		{
			pthread_create(&ledTh_id,NULL,&ledThFunc,NULL);
			
		}
			
	sleep(1);
	
}
	ledLibExit();

}
	



