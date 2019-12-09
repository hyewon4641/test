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

#include "touch.h"
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

static pthread_t touchTh_id;
static pthread_t clockTh_id;
static int fd=0;
static void touchThFunc(void*);
static void clockThFunc(void*);

static msgID=0;

int touchLibInit(void)
{
	msgID=msgget(MESSAGE_ID,IPC_CREAT|0666);
	int err1=pthread_create(&clockTh_id,NULL,&clockThFunc,NULL);
	int err=pthread_create(&touchTh_id,NULL,&touchThFunc,NULL);
	if(err==0)
		printf("thread create success\n"); 
}

int touchLibExit(void)
{
	pthread_cancel(touchTh_id);
	pthread_cancel(clockTh_id);
	close(fd);
}

void touchThFunc(void* Arg)
{
	fd=open(TOUCH_DRIVER_NAME,O_RDONLY);
	printf("touchThFunc sucess\n");
	COMMON_MSG_T msgTx;
	msgTx.messageNum=1;
	struct input_event stEvent;

	while(1)
	{
		ssize_t nread=read(fd,&stEvent,sizeof(stEvent));
	/*	if(nread==-1)
		{
			printf("read failed\n");
		continue;
		}*/
		if (stEvent.type == EVENT_TYPE && (stEvent.code == EVENT_CODE_X
                      || stEvent.code == EVENT_CODE_Y)) 
            {
				/* TODO: convert value to pixels */
				printf("%s = %d\n", stEvent.code == EVENT_CODE_X ? "X" : "Y", stEvent.value);		
			if(stEvent.code==EVENT_CODE_X)
			msgTx.whosend=2; //X 2, Y 3
			else if(stEvent.code==EVENT_CODE_Y)
			msgTx.whosend=3;
		
			msgTx.realdata=stEvent.value;
			int returnValue=msgsnd(msgID,&msgTx,sizeof(int),0);
			if(returnValue>0)
		printf("msgsnd success\n");
		}
	}
}

void clockThFunc(void* Arg)
{
	COMMON_MSG_T msgclockTx;
	msgclockTx.messageNum=1;
	msgclockTx.whosend=0;
	
	while(1)
	{
		msgclockTx.realdata = 999;
		msgsnd(msgID,&msgclockTx,sizeof(int),0);
		//sleep(0.1);
		usleep(100*1000);//100ms
	}
}
	
