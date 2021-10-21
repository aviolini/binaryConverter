
MYBIN	=	randomNum sizeof toBits toDec

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

PATHINSTALL = $(HOME)/bin

KEYWORD	=	\#thisIsTheUtilsBinPath

TEST	=	cat ~/.bashrc | grep 'export PATH="$$PATH:$(PATHINSTALL)"'

EXPR	=	 echo 'export PATH="$$PATH:$(PATHINSTALL)" $(KEYWORD)'  >> $(HOME)/.bashrc

all		:	
			$(CC) $(CFLAGS) -o randomNum randomNum.c
			$(CC) $(CFLAGS) -o sizeof sizeof.c
			$(CC) $(CFLAGS) -o toBits toBits.c
			$(CC) $(CFLAGS) -o toDec toDec.c

clean	:
			$(RM) $(MYBIN)

fclean	:	clean

re		:	fclean all

install	: 	$(MYBIN)
			install -d $(PATHINSTALL)
			install -m 744 $(MYBIN) $(PATHINSTALL)
			$(TEST) || $(EXPR)
			$(RM) $(MYBIN)

uninstall:	fclean
			$(RM) $(PATHINSTALL)/randomNum
			$(RM) $(PATHINSTALL)/sizeof
			$(RM) $(PATHINSTALL)/toBits
			$(RM) $(PATHINSTALL)/toDec

remove	:	uninstall
			rm -rf $(PATHINSTALL)
			$(TEST) && sed -i '/$(KEYWORD)/d' $(HOME)/.bashrc || echo -n

./PHONY	:	all re clean fclean install uninstall remove
