#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"

#ifndef __FND_DRV_H__
#define __FND_DRV_H__
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#define MODE_STATIC_DIS		0
#define MODE_TIME_DIS		1
#define MODE_COUNT_DIS		2

typedef struct FNDWriteDataForm_tag
{
char DataNumeric[FND_DATA_BUFF_LEN]; //숫자 0-9
char DataDot[FND_DATA_BUFF_LEN]; //숫자 0 or 1
char DataValid[FND_DATA_BUFF_LEN]; //숫자 0 or 1
}stFndWriteForm,*pStFndWriteForm;
#endif// __FND_DRV_H__

#define FND_DRIVER_NAME "/dev/perifnd"

int fndDisp(int num , int dotflag)
 //0-999999 숫자, 비트로 인코딩된 dot on/off
{
	int fd;
	int temp,i;
	stFndWriteForm stWriteData;
	for (i = 0; i < MAX_FND_NUM ; i++ )  
	{
		stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
		stWriteData.DataValid[i] = 1;
	}
	// if 6 fnd
	temp = num % 1000000; stWriteData.DataNumeric[0]= temp /100000;
	temp = num % 100000; stWriteData.DataNumeric[1]= temp /10000;
	temp = num % 10000; stWriteData.DataNumeric[2] = temp /1000;
	temp = num %1000; stWriteData.DataNumeric[3] = temp /100;
	temp = num %100; stWriteData.DataNumeric[4] = temp /10; 
	stWriteData.DataNumeric[5] = num %10; 
	// i에 여섯자리의 숫자를 입력하고 각 자리 수를 배열에 입력 
	
	fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	// 오류확인 
	{
	//	perror("driver open error.\n");
		return 0;
	}
	write(fd, &stWriteData, sizeof(stFndWriteForm));
	close(fd);
	return 1;
}

int fndOff() 
// fnd 종료 
{
	int fd,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	 // off하기 위해 전부 0으로 설정 
	fd = open(FND_DRIVER_NAME,O_RDWR); 
	//파일 open
	if ( fd < 0 ) 
	// 파일 open error
	{
		perror("driver open error.\n");
		return 0;
	}	
	
	write(fd,&stWriteData,sizeof(stFndWriteForm)); //fnd write
	close(fd); 
	// 종료 
	return 1;
}

