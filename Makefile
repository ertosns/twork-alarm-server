all: build install run

build: server.c
	gcc -g3 -o server server.c
run: server
	alarm-server
install: build
	chmod 777 server
	chmod 777 gpio.sh

	cp -rf server /usr/local/bin/alarm-server
	cp -rf gpio.sh /usr/local/bin/alarm-gpio
