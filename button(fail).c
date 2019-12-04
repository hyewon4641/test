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
#include <pthread.h>
#include "button.h"

static int fd=0;
static pthread_t buttonTh_id;

static void buttonThFunc(void*);

static mssgID=0;

int buttonLibInit(void)
{
	mssgID=msgget(MESSAGE_ID,IPC_CREAT|0666); 

	int error=pthread_create(&buttonTh_id,NULL,&buttonThFunc,NULL);
	if(error==0)  
		printf("thread create success\n"); 
} 

int buttonLibExit(void) 
{
	pthread_cancel(buttonTh_id);
	close(fd);
}

void buttonThFunc(void* Arg) 
{
	fd=open(BUTTON_DRIVER_NAME,O_RDONLY);
	if ( fd < 0 ) 
	// 파일 open error
	{
		error("driver open error.\n");
		return 0;
	}	
	printf("buttonThFunc sucess\n");
	BUTTON_MSG_T msgTx;
	msgTx.messageNum=1;

	struct input_event stEvent;
	printf("33");
	
	while(1)
	{
		printf("3");
		ssize_t nread=read(fd,&stEvent,sizeof(stEvent));
		// 버튼을 read
		if(nread==-1)
		{
			printf("failed\n");
		continue;
		}
		
		if((stEvent.type==EV_KEY)&&(stEvent.value==0))
		{
			msgTx.keyInput=stEvent.code;
			int returnValue=msgsnd(mssgID,&msgTx,sizeof(int),0);
			if(returnValue>0)
		printf("success\n");
		}
	}
}


