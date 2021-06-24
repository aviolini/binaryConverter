#!/bin/bash

gcc -Wall -Wextra -Werror pipe.c -o pipe && valgrind -s -q --track-origins=yes ./pipe ls "|" grep o "|" grep a "|" grep  e "|" wc -l