#!/bin/bash


echo testing one_pipe:
echo
gcc -Wall -Wextra -Werror one_pipe.c -o one_pipe && ./one_pipe ls cat -e
echo
echo
echo testing three_pipes:
echo
gcc -Wall -Wextra -Werror three_pipes.c tools.c -o three_pipes && ./three_pipes ls cat -e cat -n cat -t
echo
echo
echo testing multi_pipes_matr:
echo
gcc -Wall -Wextra -Werror multi_pipes_matr.c tools.c -o multi_pipes_matr && ./multi_pipes_matr ls "|" cat -e "|" cat -n "|" cat -t #"|" wc -l
# echo
# echo
# echo testing multi_pipes_list:
# echo
# gcc -Wall -Wextra -Werror multi_pipes_list.c tools.c -o multi_pipes_list && ./multi_pipes_list ls "|" cat -e "|" cat -n "|" cat -t #"|" wc -l