#!/bin/bash
echo 44 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio44/direction

