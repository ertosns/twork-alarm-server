#/bin/bash

alarm_gpio () {     
    #pin 17
    if [ ! -h /sys/class/gpio/gpio17 ]; then
	echo 17 >/sys/class/gpio/export
    fi
    echo out> /sys/class/gpio/gpio17/direction &&
        echo $1 > /sys/class/gpio/gpio17/value 
    #pin 27
    if [ ! -h /sys/class/gpio/gpio27 ]; then
	echo 27 >/sys/class/gpio/export
    fi
    echo out> /sys/class/gpio/gpio27/direction &&
        echo $2 > /sys/class/gpio/gpio27/value
}

alarm_gpio $@
