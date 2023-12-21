#!/bin/bash

while true; do
	clear

	if cc -Wall -Wextra -Werror main.c -o printf_toaster; then

	./printf_toaster
fi
	sleep 2
done

