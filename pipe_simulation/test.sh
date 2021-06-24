#!/bin/bash

gcc -Wall -Wextra -Werror pipe.c -o pipe && ./pipe ls "|" grep o "|" grep a "|" grep  e "|" wc -l 