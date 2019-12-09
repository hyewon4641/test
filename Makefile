all: libMyPeri.a buttontest.elf ledtest.elf buzzertest.elf bitmap.elf fndtest.elf touchtest.elf

buttontest.elf: buttontest.c button.h
	arm-linux-gnueabi-gcc --static -o buttontest.elf buttontest.c -l MyPeri -L. -lpthread

ledtest.elf: ledtest.c led.h
	arm-linux-gnueabi-gcc --static -o ledtest.elf ledtest.c -l MyPeri -L.

buzzertest.elf:buzzertest.c libbuzzer.h
	arm-linux-gnueabi-gcc --static -o buzzertest.elf buzzertest.c -l MyPeri -L.

bitmap.elf:bitmap.c libBitmap.h
	arm-linux-gnueabi-gcc --static -o bitmap.elf bitmap.c -l MyPeri -L.

fndtest.elf:fndtest.c fnd.h led.h
	arm-linux-gnueabi-gcc --static -o fndtest.elf fndtest.c -l MyPeri -L. -lpthread
	
touchtest.elf:touchtest.c touch.h
	arm-linux-gnueabi-gcc --static -o touchtest.elf touchtest.c -l MyPeri -L. -lpthread
	
libMyPeri.a: touch.c touch.h button.h button.c led.h led.c buzzer.c libbuzzer.h fnd.c fnd.h libBitmap.c libBitmap.h bitmapFileHeader.h
	arm-linux-gnueabi-gcc -c button.c -o button.o -lpthread
	arm-linux-gnueabi-gcc -c touch.c -o touch.o -lpthread
	arm-linux-gnueabi-gcc -c led.c -o led.o 
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
	arm-linux-gnueabi-gcc -c libBitmap.c -o libBitmap.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o libBitmap.o fnd.o touch.o

clean:
	rm -f *.elf *.o *.a
	
              
              

              
