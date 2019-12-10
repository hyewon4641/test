#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libbuzzer.h"

 char musicnote7[2000]=															//
"G   B   ^D   ^F#  ^G   ^F#   ^E-^D   "
"   ^A   ^G   ^G   ^F#-^G   ^F#   ^E-^D  "
"   ^C   ^E   ^G   ^A-^Bb   ^A   ^G-^E  "
"   ^C   ^D#   ^G   ^A-^Bb   ^A   ^F-^D#  "
"   ^G   ^A   ^F#   ^G  ^E   ^F#   ^E-^D#  "
"   ^B   ^A   ^G   ^F#  ^E   ^F#   ^E-^D#  "
"   ^D   ^E   ^G  ^D  ^C    "
"   ^B   ^A   ^G   ^E   ^D#   ^A     ^B   ^A-^G  ";
 
 char musicnote8[2000]=																	//jingle bell
 "B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B    "
 " B B  A  A--B  A      ^D-^D    "
 "  B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B  "
 " B ^D  ^D  ^C  A  G       "
 "          D  B  A  G  D-D        D  D  B  A  G  E-E    "
 "      E  E  ^C  B  A  #F-#F          ^D  ^D  ^C  A  B-B-G    "
 "       D  B  A  G  D-D        D  D  B  A  G  E-E   "
 "        E  E  ^C  B  A  ^D  ^D  ^D  ^D  ^E  ^D  ^C  A  G-G    "
 "    ^D  B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B    "
 "  B B  A  A--B  A        ^D-^D    "
 " B  B  B       B  B  B      B  ^D  G    A-B-B    "
 "         ^C  ^C  ^C     ^C-^C  B  B "
 "  B  ^D  ^D  ^C  A  G-G   ";
 
 char musicnote9[2000]=																	//santa claus is coming to town
 "^C    A-Bb   ^C     ^C-^C       "
 "    ^D-^E     ^F      ^F-^F      "
 "    A-Bb    ^C      ^C   "
 "   ^C     ^D-^C    Bb     Bb-Bb    "
 "    A      ^C      F      A      G      Bb-Bb       E      F    "
 
 "    ^C    A-Bb   ^C     ^C-^C       "
 "    ^D-^E    ^F      ^F-^F      "
 "    A-Bb    ^C      ^C   "
 "   ^C     ^D-^C    Bb     Bb-Bb    "
 "    A      ^C      F      A      G      Bb-Bb       E       F        "
 "       ^F     ^G     ^F     ^E     ^F     ^D     ^D-^D        "
 "    ^F     ^G     ^F     ^E     ^F     ^D-^D        "
 "    ^G     ^A     ^G     ^F#     ^G     ^E     ^E     ^E    "
 "   ^E-^F    ^G     ^F     ^E     ^D     ^C-^C    ";
 
 "    ^C    A-Bb   ^C     ^C-^C       "
 "    ^D-^E     ^F      ^F-^F      "
 "    A-Bb    ^C      ^C   "
 "   ^C     ^D-^C    Bb     Bb-Bb    "
 "    A      ^C      F      A      G      Bb-Bb       E      F    "
 

int main(void)
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
		//if (note == musicNote2)
	 	//note = musicNote1;
		// if (note == musicNote3)
			//note = musicNote2;
//	else note = musicNote1;
	
}
	
	

