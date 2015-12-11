# Beaglebone-lcd-c
library para el beaglebone con una lcd JHD162A

To know how to wire the lcd to the beaglebone check the 'Wiring-lcd-bb'

The libraries used for the beaglebone-lcd communication are taken from:
https://github.com/nunoalves/BeagleBone-HD44780
it was modified to our use since those libraries dont work with newer beaglebone kernel
so we based on those came up with new_beagle_gpio.c and beagle_hd44780.c this last one also slighty modified to our use.

to test the bbb is sending text to lcd use the example_04.c also taken from the github mentioned earlier but also modified to our pins
compile instructions on 'Compilar' file

the Chat-lcd.c code send a string of lcd is working then it receives what you write in the console and print it on the lcd. To send message use enter.
compile instructions on 'Compilar' file

prueba.c is a program where you read a dht sensor and print the readings to a lcd
it uses the following libraries: bbb_dht_read bbb_mmio common_dht_read taken from https://github.com/adafruit/Adafruit_Python_DHT/tree/master/source/Beaglebone_Black
and the prueba.c based on the RaspberryPi version https://github.com/adafruit/Adafruit-Raspberry-Pi-Python-Code/blob/master/Adafruit_DHT_Driver/Adafruit_DHT.c
adapted to beaglebone.
