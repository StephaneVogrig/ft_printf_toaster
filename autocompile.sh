#!/bin/bash

while true; do
	clear

	cc -Wall -Wextra -Werror *.c -o printf_toaster

	./printf_toaster
	sleep 5
done

