all: libMyPeri.a buttontest.elf ledtest.elf buzzertest.elf

buttontest.elf: buttontest.c button.h
	arm-linux-gnueabi-gcc --static -o buttontest.elf buttontest.c -l MyPeri -L. -lpthread

ledtest.elf: ledtest.c led.h
	arm-linux-gnueabi-gcc --static -o ledtest.elf ledtest.c -l MyPeri -L.

buzzertest.elf:buzzertest.c libbuzzer.h
	arm-linux-gnueabi-gcc --static -o buzzertest.elf buzzertest.c -l MyPeri -L.
	
libMyPeri.a: button.h button.c led.h led.c buzzer.c libbuzzer.h
	arm-linux-gnueabi-gcc -c button.c -o button.o -lpthread
	arm-linux-gnueabi-gcc -c led.c -o led.o 
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o

clean:
	rm -f *.elf *.o *.a
	
              
              

              
