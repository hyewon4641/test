
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "touch.h"

int main(void)
{
	int x;
	int y;
	int realx;
	int realy;
	int cnt;
	touchLibInit();
	COMMON_MSG_T msgRx;
	int msgID=msgget(MESSAGE_ID,IPC_CREAT|0666);

	if(msgID==-1)
	{
		printf("Cannot get msgID\n");
		return -1;
	}

	while(1)
	{   
		int reValue=0;
		reValue=msgrcv(msgID,&msgRx,sizeof(int),0,0);
		
		switch(msgRx.whosend)
		{
			case 2: x=msgRx.realdata; cnt=3; break;
			case 3: y=msgRx.realdata; cnt=3;break;
			case 4: 
				if(cnt==0)
				{;} //do nothing
				else if(cnt==1)
				{	
					realx=x; realy=y;
					printf("x=%d,y=%d\n",realx,realy);
				}
				else
				{cnt--;}
				
				break;
		}
		
	}
	touchLibExit();
}
			
