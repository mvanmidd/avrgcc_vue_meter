# Makefile to build light_ws2812 library examples
# This is not a very good example of a makefile - the dependencies do not work, therefore everything is rebuilt every time.

# Change these parameters for your device

F_CPU = 16000000
DEVICE = atmega32u4

programmerDev=`ls /*/cu.usb*`
programmerType=avr109

# Tools:
CC = avr-gcc

LIB       = light_ws2812
# EXAMPLES  = RGB_blinky RGBW_blinky Chained_writes Rainbow
EXAMPLES  = main
# DEP		  = ws2812_config.h Light_WS2812/light_ws2812.h
DEP		  = light_ws2812.h

CFLAGS = -g2 -I. -ILight_WS2812 -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions
CFLAGS+= -Wall -Wno-pointer-to-int-cast
#CFLAGS+= -Wa,-ahls=$<.lst

LDFLAGS = -Wl,--relax,--section-start=.text=0,-Map=main.map

all:	$(EXAMPLES)
# all: main.hex


$(LIB): $(DEP)
	echo Building Library
	$(CC) $(CFLAGS) -o $@.o -c $@.c


$(EXAMPLES): $(LIB)
	echo Building $@
	$(CC) $(CFLAGS) -o $@.o $@.c $^.c
	avr-size $@.o
	avr-objcopy -j .text  -j .data -O ihex $@.o $@.hex
	avr-objdump -d -S $@.o >$@.lss

flash: main.hex
	avrdude -p $(DEVICE) -c $(programmerType) -P $(programmerDev)  -v -U flash:w:$<




.PHONY:	clean

clean:
	rm -f *.hex *.o *.lss
