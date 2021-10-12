
MYBIN	=	randomNum sizeof toBits toDec

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

PATHINSTALL = ~/bin

TEST	=	cat ~/.bashrc | grep 'export PATH="$$PATH:$(PATHINSTALL)"'

EXPR	=	 echo 'export PATH="$$PATH:$(PATHINSTALL)"' >> ~/.bashrc

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

install	: 	$(MYBIN)
			install -d $(PATHINSTALL)
			install -m 744 $(MYBIN) $(PATHINSTALL)
			$(TEST) || $(EXPR)
#			source ~/.bashrc
uninstall:	fclean
			$(RM) $(PATHINSTALL)/randomNum
			$(RM) $(PATHINSTALL)/sizeof
			$(RM) $(PATHINSTALL)/toBits
			$(RM) $(PATHINSTALL)/toDec
#deve cancellare anche la riga di ~/.bashrc?
./PHONY	:	all re clean fclean
