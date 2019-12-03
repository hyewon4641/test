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
#include "led.h"

static unsigned int ledValue=0;

static int fd=0;
int ledOnOff(int ledNum,int ledOnOff)
{
	unsigned int i=1;
	
				//0x1;, ledOnOff ==2
	i=i<<ledNum;		//0x1<<2; i=0x4;
	printf ("i:0x%08x, ledNum:%d\r\n",i, ledNum);
	ledValue=ledValue&(~i);
	printf ("ledValue:0x%08x\r\n",ledValue);
	//~i = 0xfffffffC
	if(ledOnOff!=0)
	{
		printf ("ledValue or-ring. 0x%08x\r\n",i);
		ledValue |=i;
	}
	printf ("ledValue: 0x%08x\r\n",ledValue);
	write(fd,&ledValue,4);
}

int ledLibInit(void)
{
	fd=open("/dev/periled",O_WRONLY);
	ledValue=0;
}

int ledLibExit(void)
{
	ledValue=0;
	ledOnOff(0,0);
	close(fd);
}
