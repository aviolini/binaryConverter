# !/bin/bash


echo testing one_pipe:
echo
gcc -Wall -Wextra -Werror one_pipe.c -o one_pipe
valgrind -s -q --leak-check=full --track-fds=all --trace-children=yes ./one_pipe ls cat -e
echo
echo
echo testing three_pipes:
echo
gcc -Wall -Wextra -Werror three_pipes.c tools.c -o three_pipes
valgrind -s -q --leak-check=full --track-fds=all --trace-children=yes ./three_pipes ls cat -e cat -n wc -l
echo
echo
echo testing multi_pipes_matr:
echo
gcc -Wall -Wextra -Werror multi_pipes_matr.c tools.c -o multi_pipes_matr
valgrind -s -q --trace-children=yes --leak-check=full --track-fds=all ./multi_pipes_matr ls "|" cat -e "|" cat -n "|" cat -t
echo
echo
echo testing multi_pipes_list:
echo
gcc -Wall -Wextra -Werror multi_pipes_list.c tools.c -o multi_pipes_list
valgrind -s -q --trace-children=yes --leak-check=full --track-fds=all ./multi_pipes_list ls "|" cat -e "|" cat -n "|" cat -t

#--track-fds=all
#--leak-check=full
#--log-file=output1
#--track-origins=yes
#--show-leak-kinds=all