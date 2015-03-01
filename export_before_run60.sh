#!/bin/bash
echo 60 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio60/direction
