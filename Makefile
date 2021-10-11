
MYBIN	=	randomNum sizeof toBits toDec

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all		:	
			$(CC) $(CFLAGS) -o randomNum randomNum.c
			$(CC) $(CFLAGS) -o sizeof sizeof.c
			$(CC) $(CFLAGS) -o toBits toBits.c
			$(CC) $(CFLAGS) -o toDec toDec.c

clean	:
			$(RM) $(MYBIN)

fclean	:	clean
			$(RM) $(MYBIN)

re		:	fclean all

./PHONY	:	all re clean fclean
