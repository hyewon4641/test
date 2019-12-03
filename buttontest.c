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
#include "button.h"

int main(void)
{
	buttonLibInit();
	BUTTON_MSG_T msgRx;
	int msgID=msgget(MESSAGE_ID,IPC_CREAT|0666);

	if(msgID==-1)
	{
		printf("Cannot get msgID\n");
		return -1;
	}
	
	struct input_event stEvent;

	while(1)
	{   
	
		int reValue=0;
		reValue=msgrcv(msgID,&msgRx,sizeof(int),0,0);
		printf("msgrcv success");
			stEvent.code=msgRx.keyInput;
			printf("EV_KET(");
			switch (stEvent.code)
			{
			case KEY_VOLUMEUP: printf("Volume up key):");break;
		    case KEY_HOME: printf("Home key):"); break;
			case KEY_SEARCH:printf("Search key):");break;
			case KEY_BACK:printf("Back key):");break;
			case KEY_MENU:printf("Menu key):"); break;
			case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}	

	}
	buttonLibExit();
}
			
