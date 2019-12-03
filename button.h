#ifndef _BUTTON_H_
#define _BUTTON_H_
int buttonLibInit(void);
int buttonLibExit(void);

#define BUTTON_DRIVER_NAME "/dev/input/event4"
#define MESSAGE_ID	1122

typedef struct
{
	long int messageNum;
	int keyInput;
} BUTTON_MSG_T;

#endif 

