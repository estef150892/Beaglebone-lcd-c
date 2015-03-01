#!/bin/bash
echo 45 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio45/direction

