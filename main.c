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
#include "libbuzzer.h"
#include "libBitmap.h"
#include "fnd.h"
#include "textlcd.h"
#include "colorledtest.h"
#include "led.h"

 char musicnote8[2000]=
 "B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B    "
 "    B  B  A  A--B  A      ^D-^D    "
 "    B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B  "
 "    B  ^D  ^D  ^C  A  G       "
 "        D  B  A  G  D-D        D  D  B  A  G  E-E    "
 "      E  E  ^C  B  A  #F-#F          ^D  ^D  ^C  A  B-B-G    "
 "        D  B  A  G  D-D        D  D  B  A  G  E-E   "
 "        E  E  ^C  B  A  ^D  ^D  ^D  ^D  ^E  ^D  ^C  A  G-G    "
 "    ^D  B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B    "
 "    B  B  A  A--B  A      ^D-^D    "
 "    B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B  "
 "    B  ^D  ^D  ^C  A  G-G   ";
 

int realx;
int realy;
int ledcnt=5;
int thread_exit=0;
int i;


pthread_t collect_id;
pthread_t bgm_id;
pthread_t fnd_id;
pthread_t colorled_id;	


void collect(void* Arg1)
{
	int x;
	int y;
	int cnt;
	touchLibInit();
	COMMON_MSG_T msgRx;
	int msgID=msgget(MESSAGE_ID,IPC_CREAT|0666);

	if(msgID==-1)
	{
		printf("Cannot get msgID\n");
		return -1;
	}
	if(thread_exit==0)
	{
		while(1)
		{   
			int reValue=0;
			reValue=msgrcv(msgID,&msgRx,sizeof(int),0,0);
			
			switch(msgRx.whosend)
			{
				case 2: x=msgRx.realdata; cnt=3; break;
				case 3: y=msgRx.realdata; cnt=3;break;
				case 4: 
					if(cnt==0)
					{;} //do nothing
					else if(cnt==1)
					{	
						realx=x; realy=y;
						printf("x=%d,y=%d\n",realx,realy);
						
					}
					else
					{cnt--;}
				
					break;
			}	
		}
	touchLibExit();
}

void bgm(void* Arg2)
{
	libBuzzerInit();
	int i=0;
	int j=0;
	int thisScale = 0;
	char *note = musicnote8;
	
	char prevChar = 0;

		for (i=0;i<strlen(note);i++)
		{
			switch (note[i])
			{
				case ' ': case '-':	//Play scale and wait;
				//printf ("ThisScale:%d\r\n",thisScale);
				if ((prevChar!=' ') && (prevChar!= '-'))
				{
					setFrequency (thisScale);	
					buzzerEnable (1);
					usleep(250*1000);	//100ms;

					/*buzzerEnable (0);
					usleep(100*1000);	//100ms;*/
					thisScale = 0;
				}
				else if((prevChar = ' '))
				{
					buzzerEnable (0);
					usleep(50*1000);	//100ms;
					thisScale = 0;
					}
					
				else if((prevChar = '-'))
				{
					setFrequency (thisScale);
					buzzerEnable (1);
					usleep(25*1000);	//100ms;
				}

				break;
				case '^': thisScale+=HC;	break;
				case '*': thisScale+=HHC;	break;
				case 'C': thisScale += C - C;	break;
				case 'D': thisScale += D - C;	break;
				case 'E': thisScale += E - C;	break;
				case 'F': thisScale += F - C;	break;
				case 'G': thisScale += G - C;	break;
				case 'A': thisScale += A - C;	break;
				case 'B': thisScale += B - C;	break;
					
				case '#': thisScale++;	break;
				case 'b': thisScale--;	break;
			}
			prevChar = note[i];
		}
		usleep(2000*1000);
		printf("end\n");
	
}


void colorled_OnOff(void* Arg3)
{
	pwmLedInit();
	while(1)
	{
	colorled_on();
	usleep(500*1000);
	
	colorled_off();
	usleep(500*1000);
	
	if(i==0)
	break;
	
}
	pwmInactiveAll();
	
	//pthread_exit();
}

void fnd(void* Arg4)
{
	
	for(i=60;i>=0;i--)
	{
		fndDisp(i,0);
		
		
		if(i==10)
		{
			int err=pthread_create(&colorled_id,NULL,&colorled_OnOff,NULL);	
			if(err==0)
			printf("ss\n");		
		}
			sleep(1);
		 } 	
}




int main(void)
{
	int err=pthread_create(&collect_id,NULL,&collect,NULL);
	if(err!=0)
		printf("touch create failed\n");
	int err1=pthread_create(&bgm_id,NULL,&bgm,NULL);
	if(err1!=0)
		printf("bgm creat failed\n");
	int err2=pthread_create(&fnd_id,NULL,&fnd,NULL);
	if(err2!=0)
		printf("fnd creat failed\n");
	
	lcdtextInit();	
	lcdWrite("tree.bmp");
	
	if(ledcnt>0)
	{
		while(1)
		{
			if(((825<realx)&&(realx<840))&&((335<realy)&&(realy<350)))
			{
				lcdWrite("tree_great.bmp");
				lcdwrite("GREAT");
				sleep(1);
				lcdWrite("santa.bmp");
				break;
			}
			else 
			{
				lcdWrite("tree_retry.bmp");
				lcdwrite("RETRY");
				sleep(1);
				lcdWrite("tree.bmp");
			}
		}
		
		while(1)
		{
			if(((685<realx)&&(realx<700))&&((105<realy)&&(realy<120)))
			{
				lcdWrite("santa_great.bmp");
				lcdwrite("GREAT");
				sleep(1);
				lcdWrite("frozen.bmp");
				break;
			}
			else 
			{
				lcdWrite("santa_retry.bmp");
				lcdwrite("RETRY");
				sleep(1);
				lcdWrite("santa.bmp");
			}		
		}
	
			while(1)
		{
			if(((935<realx)&&(realx<950))&&((105<realy)&&(realy<120)))
			{
				lcdWrite("frozen.bmp");
				lcdwrite("GREAT");
				sleep(1);
				lcdWrite("winner.bmp");
				break;
			}
			else 
			{
				lcdWrite("frozen_retry.bmp");
				lcdwrite("RETRY");
				sleep(1);
				lcdWrite("frozen.bmp");
			}		
		}
		
	}
		lcdWrite("loser.bmp");
		thread_exit=1;
		lcdexit();
		return 0;
}
}
	
	
	
	
	
	
