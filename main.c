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
 "    B  ^D  ^D  ^C  A  G-G   "
 "    B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B  "
 "    B  ^D  ^D  ^C  A  G-G   ";
 

int realx;
int realy;

int thread_exit=0;
int i;
int touch;


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
	
		while(!thread_exit)
		{   
			int reValue=0;
			reValue=msgrcv(msgID,&msgRx,sizeof(COMMON_MSG_T) -  sizeof(long int),0,0);
			//printf ("msgRx whosend: %d %d \r\n", msgRx, whosend, cnt, reValue);
			
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
						touch = 1;
						cnt--;
						
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
			if(thred_exit==1)
			{
				buzzerEnable(0);
				break;
			}
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
		} //End of For.
		
		usleep(2000*1000);
		printf("end\n");
	buzzerEnable(0);
} //End of Func.


void colorled_OnOff(void* Arg3)
{
	pwmLedInit();
	while(!thread_exit)
	{
		colorled_on();
		usleep(500*1000);
	
		colorled_off();
		usleep(500*1000);
	
		if(i==0)
		break;
	
	}
	colorled_off();
	
	pwmInactiveAll();
	
	//pthread_exit();
}

void fnd(void* Arg4)
{
	
	for(i=60;i>=0;i--)
	{
		if(thread_exit==1) break;
		fndDisp(i,0);
		
		
		if(i==10)
		{
			int err=pthread_create(&colorled_id,NULL,&colorled_OnOff,NULL);	
			if(err==0)
			printf("ss\n");		
		}
			sleep(1);
	 } 	
		 
		 thread_exit = 1;
		 lcdWrite("loser.bmp");
		 lcdWrite("RETRY!");
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
	ledLibInit();
	ledOnOff(0,1);
	ledOnOff(1,1);
	ledOnOff(2,1);
	ledOnOff(3,1);
	ledOnOff(4,1);
	int ledcnt=5;
	lcdwrite("START!");
	
	//Game Tree
	lcdWrite("tree.bmp");
	
	while(ledcnt)
	{
		if(touch==1)
		{
			if(((830<realx)&&(realx<860))&&((320<realy)&&(realy<360)))
			{
				lcdWrite("tree_great.bmp");
				lcdwrite("GREAT");
				sleep(1);
				lcdWrite("santa.bmp");
				touch=0;
				break;
			}
			else 
			{
				lcdWrite("tree_retry.bmp");
				lcdwrite("RETRY");
				ledcnt--;
				ledOnOff(ledcnt,0);
				sleep(1);
				touch=0;
				lcdWrite("tree.bmp");
			}
		}
	}//End of Game 1 write
	
		if (ledcnt) lcdWrite("santa.bmp");
		while(ledcnt)
		{
			if(touch==1)
			{
				if(((670<realx)&&(realx<715))&&((380<realy)&&(realy<410)))
				{
					lcdWrite("santa_great.bmp");
					lcdwrite("GREAT");
					sleep(1);
					lcdWrite("frozen.bmp");
					touch=0;
					break;
				}
				else 
				{
					lcdWrite("santa_retry.bmp");
					lcdwrite("RETRY");
					ledcnt--;
					ledOnoff(ledcnt,0);
					sleep(1);
					touch = 0;
					lcdWrite("santa.bmp");
				}		
			}
		} //End of Game 2 while
		
		if (ledcnt) lcdWrite("frozen.bmp");
		while(ledcnt)
		{
			if(touch==1)
			{
				if(((920<realx)&&(realx<960))&&((95<realy)&&(realy<130)))
				{
					lcdWrite("frozen.bmp");
					lcdwrite("GREAT");
					sleep(1);
					break;
				}
				else 
				{
					lcdWrite("frozen_retry.bmp");
					lcdwrite("RETRY");
					ledcnt--;
					ledOnOff(ledcnt,0);
					sleep(1);
					lcdWrite("frozen.bmp");
				}		
			}
		} //End of Game 3 while
		
		thread_exit = 1;
		if (ledcnt)
		{
			lcdwrite("CONGRATULATION");
			lcdWrite("winner.bmp");
		}
		
		else
		{
			lcdWrite("loser.bmp");
			lcdwrite("RETRY!");
		}
		
		pthread_cancel(&collect_id);
		pthread_cancel(&bgm_id);
		pthread_cancel(&fnd_id);
		pthread_cancel(&colorled_id);
		ledLibExit();
		lcdexit();
		
		return 0;
}

	
	
	
	
	
	
