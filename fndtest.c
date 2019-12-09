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
#include "colorled.h"


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
	



