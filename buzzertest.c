#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libbuzzer.h"


//char musicNote1[2000]=
//"G  B       D   F#  G   F#     E - D
/*" ^E ^E ^E ^C ^E ^G G ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B"
" ^G ^F# ^F ^D ^E G A ^C A ^C ^D ^G ^F# ^F ^D ^E *C *C *C ^G ^F# ^F ^D ^E G A ^C A ^C ^D ^D# ^D ^C"
" ^C ^C ^C ^C ^D ^E ^C A G ^C ^C ^C ^C ^D ^E ^C ^C ^C ^C ^D ^E ^C A G ^E ^E ^E ^C ^E ^G G ^C G E"
" A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^C G E A B Bb A G ^E ^G ^A ^F ^G ^E ^C ^D B ^E-^C G G A ^F ^F A"
" B ^A ^A ^A ^G ^F ^E ^C A G ^E-^C G G A ^F ^F A B ^F ^F ^F ^E ^D ^C G E C ^C G E A B A G# Bb G# G-F#-G ";*/
//FROM https://noobnotes.net/super-mario-bros-theme-nintendo/?solfege=false&transpose=0

char musicNote3[2000]=
"C  E       G   B  ^C   B     A - G "
" ^D          ^C    ^C     B     ^C   B  A-G "
" F     A       ^C    ^D-^D#    ^D       ^C-A "
" F - G# - ^C        ^D        ^D# - ^D     Bb-G#"
" ^C    ^D     B    ^C    A     B   A-G#"
" ^E             ^D      ^C      B      A-B   A-G#"
" G           A      ^C      ^G     ^F"
" ^E   ^D     ^C     A       G# - ^D    ^E   ^D-^C ";
char musicNote2[2000]=
" C   A   G    Bb      C  F  E  F"
" C     A      G      Bb    C    F-E-F"
" A   Bb    ^C    ^D     ^C - G     G  A  Bb-^C  A"
" A      Bb     ^C      ^D     ^C - G    G-A  Bb  ^C   A"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb - ^C             ^D       ^E     ^D-^C-Bb    A   ^C"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb       ^C      ^D      ^E      ^D     ^C    Bb   A     ^C"
" C       A      G       Bb      C   F  E   F"
" C   A   G    Bb     C  F-E-F"
" C     A     G      Bb-G     C-F-G-A"
" A      Bb      ^C-^D-^C-G         G      A     Bb      ^C      A"
" A  -  Bb         ^C           ^D         ^C - G       G     A-Bb-^C   A"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb - ^C             ^D       ^E     ^D-^C-Bb    A   ^C"
" ^C   ^D-^E   ^F   ^E-Bb"
" Bb       ^C      ^D      ^E      ^D     ^C    Bb   A     ^C"
" C       A      G       Bb      C   F  E   F"
" C       A      G       Bb      C   F  E   F"
" C   F  E   F";

char musicNote4[2000]=
"E          F  -  E      D  E     F         F# - G"
"A         B   ^C  ^D  ^C   B     A      G"
"C              D        E - E        E - A      G       C - C      C - G"
"F        E          F   -   E       D    C     D"
"E        F   -   E      D  E      F        F#  -  G"
"A         B-^C       ^D- C         B    A    G"
"C          D        E      E    E - A      G      ^C"
"C         D     E       E         A - D - C      D      C";

char musicNote5[2000]=
"D          D     G     G"
"D          D      A       A"
"A      G     A      A     G      A-B        ^C    B   B"
"D - D          G      G"
"D         D      A       A"
"G          A       B       ^C"
"A     B  ^C   G  G  ^D"
"^C            A    A     A      A-B-^C"
"A     B  ^C    G ^E ^E-^D"
"^C   ^D-^E  ^E  ^F-^E ^D-^C ^D-^C"
"^G ^E ^D"
"^C           ^C        ^G    ^E   ^C"
"^C     ^C       B        G     G"
"F         F       F - E       F - E       F      F-E-C";

 char musicnote6[2000]=
"    C - C           G - G      A-A     G     "
//Twinkle, twinkle, little star

" F        F     E-E         D       D      C     "
//How I wonder what you are!

" G      G-F      F       E        E     D     "
//Up above the world so high,

" G       G      F-F      E     E     D     "
//Like a diamond in the sky...

" C - C           G - G      A-A     G     "
//Twinkle, twinkle, little star

" F        F     E-E         D       D      C   ";
//How I wonder what you are!

int main(void)
{
	libBuzzerInit();
	int i=0;
	int j=0;
	int thisScale = 0;
	char *note = musicnote6;
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
					usleep(500*1000);	//100ms;

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
		usleep(1000*1000);
		printf("end\n");
		//if (note == musicNote1)
	 	//note = musicNote2;
		// if (note == musicNote2)
			//note = musicNote3;
//	else note = musicNote2;
	
}
	
	

