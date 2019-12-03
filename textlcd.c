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
#include "textlcddrv.h"
#include "textlcd.h"




#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

void doHelp(void)
{
	printf("usage: textlcdtest <linenum> <'string'>\n");
	printf("       linenum => 1 ~ 2\n");	
	printf("  ex) textlcdtest 2 'test hello'\n");
	
}

void init(void)
{
	unsigned int linenum = 0;

	stTextLCD  stlcd; 
	int fd;
	int len; 
	
	memset(&stlcd,0,sizeof(stTextLCD));
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
}

void lcdwrite(const char *str1, const char *str2, int lineFlag)
{
	if ( lineFlag == 1) // firsst line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	}
	else if ( lineFlag == 2) // second line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	}
	else 
	{
		printf("lineFlag : %d  wrong .  range (1 ~ 2)\n", lineFlag);
		return 1; 
	}
	printf("string:%s\n",argv[2]);
	len = strlen(argv[2]);
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],argv[2],COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],argv[2],len);
	}
	stlcd.cmd = CMD_WRITE_STRING;
	// open  driver 
	write(fd,&stlcd,sizeof(stTextLCD));
	}

void lcdexit(void)
{
	close(fd);
	
	return 0;
}







