# baud=115200
avrType=atmega32u4
avrFreq=16000000 # 16 Mhz
# programmerDev=/dev/ttyUSB0
programmerDev=`ls /*/cu.usb*`
programmerType=avr109
# programmerType=usbasp


cflags=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Wall -Werror -Wextra -Os \
	-nostdlib -nostartfiles \
	-I/Users/markvan/devel/keyboard/vumeter/Adafruit_NeoPixel \
	-I/Users/markvan/devel/keyboard/qmk_firmware/drivers \
	-I/Users/markvan/devel/keyboard/qmk_firmware/quantum \
	-I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino -I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/leonardo

objects=$(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: flash clean

all: main.hex

%.o: %.c
	avr-gcc $(cflags) -c $< -o $@

main.elf: $(objects)
	avr-gcc $(cflags) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

flash: main.hex
	# avrdude -p$(avrType) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -U flash:w:$<
	avrdude -p $(avrType) -c $(programmerType) -P $(programmerDev)  -v -U flash:w:$<

clean:
	rm -f main.hex main.elf $(objects)
