
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
#include "colorledtest.h"

int main(void)
{
	pwmLedInit();
	int i;
	for(i=0; i<20; i++)
	{
		colorled_on();
		usleep(500*1000);
		colorled_off();
		usleep(500*1000);
	}
	pwmInactiveAll();
	
	return 0;
}
