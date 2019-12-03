#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "libbuzzer.h"

//#define MAX_SCALE_STEP		8
#define BUZZER_BASE_SYS_PATH	"/sys/bus/platform/devices/"
#define BUZZER_FILENAME 		"peribuzzer"
#define BUZZER_ENABLE_NAME		"enable"
#define BUZZER_FREQUENCY_NAME	"frequency"


static char gBuzzerBaseSysDir[128];

const int musicScale[LAST_SCALE] =
{
	262, 	// do
	277,	// do+
	294,	// Re
	311,	// Re+
	330,	//E
	349,	//F
	370,	//F+
	392,	//G
	415,	//G+
	440,	//A
	466,	//A+
	494,  	//B
	2*262, 	// do
	2*277,	// do+
	2*294,	// Re
	2*311,	// Re+
	2*330,	//E
	2*349,	//F
	2*370,	//F+
	2*392,	//G
	2*415,	//G+
	2*440,	//A
	2*466,	//A+
	2*494,  	//B	
};

int findBuzzerSysPath(void)
{
	DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
	int ifNotFound = 1;
	if (dir_info != NULL)
	{
		while (1)
		{	
			struct dirent  *dir_entry;
			dir_entry = readdir (dir_info);
			if (dir_entry == NULL)	break;
			if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
			{
				ifNotFound = 0;
				sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
			}
		}
	}
	printf("find %s\n",gBuzzerBaseSysDir);

	return ifNotFound; 
}
void buzzerEnable(int bEnable)
{
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	int fd=open(path,O_WRONLY);
	if ( bEnable)		write(fd, &"1", 1);
	else 				write(fd, &"0", 1);
	close(fd);
}
void setFrequency(int scale) 
{
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	//printf ("Write Buf: %d\r\n",musicScale[scale]);
	dprintf(fd, "%d", musicScale[scale]);
	close(fd);
}
void libBuzzerInit(void)
{
	findBuzzerSysPath();
}
