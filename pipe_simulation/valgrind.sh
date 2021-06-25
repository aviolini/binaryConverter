# !/bin/bash


echo testing one_pipe:
echo
gcc -Wall -Wextra -Werror one_pipe.c -o one_pipe
valgrind -s --track-origins=yes --leak-check=full --trace-children=yes ./one_pipe ls grep o
echo
echo
echo testing three_pipes:
echo
gcc -Wall -Wextra -Werror three_pipes.c tools.c -o three_pipes
valgrind -s -q --track-origins=yes --leak-check=full --track-fds=all --trace-children=yes ./three_pipes ls grep o grep t wc -l
echo
echo
echo testing multi_pipes:
echo
gcc -Wall -Wextra -Werror multi_pipes.c tools.c -o multi_pipes
valgrind -s -q --trace-children=yes --leak-check=full ./multi_pipes ls "|" grep o "|" grep t "|" grep e "|" grep g "|" cat -e 


#--track-fds=all
#--leak-check=full
#--log-file=output1
#--track-origins=yes
#--show-leak-kinds=all