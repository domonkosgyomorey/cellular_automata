#!/bin/sh

gcc -Wall -Wextra -g ./src/main.c ./src/gol.c ./src/elementary_ca.c -o main -lSDL2
