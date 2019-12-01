
#include <stdio.h>
#include <stdlib.h>

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
