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
#include "led.h"
#define LED_DRIVER_NAME "/dev/periled"

int main(void)
{
	
	 ledLibInit();
	 

	  sleep(1);
	  ledOnOff(0,0);
	  
	 ledLibExit();

 }
 
