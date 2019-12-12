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

static pthread_t buttonTh_id;
static int fd=0;
static void buttonThFunc(void*);

static msgID=0;

int buttonLibInit(void)
{
	
	msgID=msgget(MESSAGE_ID,IPC_CREAT|0666); 
	// message get
	int err=pthread_create(&buttonTh_id,NULL,&buttonThFunc,NULL);
	if(err==0) // thred 오류 
		printf("thread create success\n"); 
} 
// 에러 확인 

int buttonLibExit(void) 
//button 사용 종료 
{
	pthread_cancel(buttonTh_id);
	close(fd);
}

void buttonThFunc(void* Arg) 
//button thred 실행 함수 
{
	fd=open(BUTTON_DRIVER_NAME,O_RDONLY);
	if ( fd < 0 ) 
	// 파일 open error
	{
		perror("driver open error.\n");
		return 0;
	}	
	printf("buttonThFunc sucess\n");
	BUTTON_MSG_T msgTx;
	msgTx.messageNum=1;
	struct input_event stEvent;
	printf("22");
	
	while(1)
	{
		printf("2");
		ssize_t nread=read(fd,&stEvent,sizeof(stEvent));
		if(nread==-1)
		{
			printf("read failed\n");
		continue;
		}
		
		if((stEvent.type==EV_KEY)&&(stEvent.value==0))
		{
			msgTx.keyInput=stEvent.code;
			int returnValue=msgsnd(msgID,&msgTx,sizeof(int),0);
			if(returnValue>0)
		printf("msgsnd success\n");
		}
	}
}


