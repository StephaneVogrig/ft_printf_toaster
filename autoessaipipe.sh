#!/bin/bash

while true; do
	clear

	cc -Wall -Wextra -Werror essai_pipe.c -o essaipipe

	./essaipipe
	sleep 5
done

