#!/bin/bash
echo 26 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio26/direction

