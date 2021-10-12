
MYBIN	=	randomNum sizeof toBits toDec

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

PATHINSTALL = $(HOME)/bin

#VAR		=	'export PATH="$$PATH:$(PATHINSTALL)"'

TEST	=	cat ~/.bashrc | grep 'export PATH="$$PATH:$(PATHINSTALL)"'

#TEST1	=	$(cat ~/.bashrc | grep -n 'export PATH="$$PATH:$(PATHINSTALL)"'| cut -d: -f1)

EXPR	=	 echo 'export PATH="$$PATH:$(PATHINSTALL)"' >> $(HOME)/.bashrc

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
			
#			$(TEST) && sed -i "${TEST1}d" $(HOME)/.bashrc
#			rimuovere la riga da bashrc			

./PHONY	:	all re clean fclean
