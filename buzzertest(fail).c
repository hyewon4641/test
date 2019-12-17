#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libbuzzer.h"

char musicnote1[2000]=																	
 "D    C     D     F   B    B     "
 "    ^D-^E     ^C      ^E-^F      "
 "    C-Bb    D      ^F   "
 "   ^E     ^D-^E    D     Fb-Fb    "
 "    A      ^E      D      B      D     Bb-Bb       E      F    "
 
 "    ^C    A-A   ^E     ^C-^C       "
 "    ^D-^E    ^F      C-^C      "
 "    A-Bb    D      ^C   "
 "   ^C     ^C    Cb     Bb    "
 "    A      ^E     E         D      Bb-Bb       E       F        ";

 

int main(void)
{
	libBuzzerInit();
	int i=0;
	int j=0;
	int thisScale = 0;
	char *note = musicnote1;
	char prevChar = 0;

		for (i=0;i<strlen(note);i++)
		{
			switch (note[i])
			{
				case ' ':
        case '-':	
			
				if (prevChar!=' ') 
				{
					setFrequency (thisScale);	
					buzzerEnable (1);
					usleep(250*1000);
					thisScale = 0;
				}
                if(prevChar!= '-')
{
					setFrequency (thisScale);	
					buzzerEnable (1);
					usleep(250*1000);
					thisScale = 0;
				}
				else if((prevChar = ' '))
				{
					buzzerEnable (0);
					usleep(50*1000);	//100ms;
					thisScale = 0;
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
	
	

