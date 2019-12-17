
all: libMyPeri.a main.elf

main.elf:main.c libMyPeri.a
	arm-linux-gnueabi-gcc --static -o main.elf main.c -l MyPeri -L. -lpthread
	
libMyPeri.a:colorledtest.c colorledtest.h touch.c touch.h led.h led.c buzzer.c libbuzzer.h fnd.c fnd.h libBitmap.c libBitmap.h bitmapFileHeader.h textlcd.c textlcd.h
	arm-linux-gnueabi-gcc -c touch.c -o touch.o -lpthread
	arm-linux-gnueabi-gcc -c led.c -o led.o 
	arm-linux-gnueabi-gcc -c textlcd.c textlcd.h
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
	arm-linux-gnueabi-gcc -c libBitmap.c -o libBitmap.o
	arm-linux-gnueabi-gcc -c colorledtest.c -o colorledtest.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o buzzer.o libBitmap.o fnd.o touch.o colorledtest.o textlcd.o
clean:
	rm -f *.elf *.o *.a
	
              
              

              
