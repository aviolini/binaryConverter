#!/bin/bash
echo testing one_pipe:
echo
gcc -Wall -Wextra -Werror one_pipe.c -o one_pipe
valgrind -s -q --track-origins=yes --trace-children=yes ./one_pipe ls grep o
echo
echo
echo testing three_pipes:
echo
gcc -Wall -Wextra -Werror three_pipes.c tools.c -o three_pipes
valgrind -s -q --track-origins=yes --trace-children=yes ./three_pipes ls grep o grep t wc -l
echo
echo
echo testing multi_pipes:
echo
gcc -Wall -Wextra -Werror multi_pipes.c tools.c -o multi_pipes
valgrind -s -q --track-origins=yes --trace-children=yes ./multi_pipes ls "|" grep o "|" grep a "|" grep  e "|" wc -l 