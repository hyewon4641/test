#ifndef _TOUCH_H_
#define _TOUCH_H_
int touchLibInit(void);
int touchLibExit(void);

#define TOUCH_DRIVER_NAME "/dev/input/event4"
#define MESSAGE_ID 2211

typedef struct
{
	long int messageNum;
	int whosend;	//if 0: Timer, if 1: button, if 2: TouchX, if 3: TouchY
	int realdata;	//whosend 0: no, 1: button Key, 2: X coord. 3: Y coord
} COMMON_MSG_T;

#endif 




