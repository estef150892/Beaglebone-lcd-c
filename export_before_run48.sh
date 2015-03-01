#!/bin/bash
echo 48 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio48/direction

