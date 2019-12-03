#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "fnd.h"


int main(void)
{
	printf("start\n");
	if (mode == MODE_STATIC_DIS )
	{
	fndDisp(number , 0);	
	}
	else if(mode == MODE_TIME_DIS )
	{
	struct tm *ptmcur;
	time_t tTime;
	if ( -1 == time(&tTime) )
	return -1;
	ptmcur = localtime(&tTime);
	number = ptmcur->tm_hour * 10000;
	number += ptmcur->tm_min *100;
	number += ptmcur->tm_sec;
	fndDisp(number , 0b1010);
	}
	else if (mode == MODE_COUNT_DIS)
	{
	counter = 0;
	while(1)
	{
	if (!fndDisp(counter , 0))
	break;
	counter++;
	sleep(1);
	if (counter > number )
	break;
	}
}
	


