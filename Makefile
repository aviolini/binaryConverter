
MYBIN		=	randomNum sizeof toBits toDec

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

BINPATH		=	$(HOME)/bin

UTILSPATH	=	utils

KEYWORD		=	\#thisIsTheUtilsBinPath

TEST		=	cat ~/.bashrc | grep 'export PATH="$$PATH:$(BINPATH)/$(UTILSPATH)"'

EXPR		=	echo 'export PATH="$$PATH:$(BINPATH)/$(UTILSPATH)" $(KEYWORD)'  >> $(HOME)/.bashrc

UNINSTALL	=	$(BINPATH)/$(UTILSPATH)/uninstall-utils.sh

all			:	
				$(CC) $(CFLAGS) -o randomNum randomNum.c
				$(CC) $(CFLAGS) -o sizeof sizeof.c
				$(CC) $(CFLAGS) -o toBits toBits.c
				$(CC) $(CFLAGS) -o toDec toDec.c

clean		:
				$(RM) $(MYBIN)

fclean		:	clean

re			:	fclean all

install		:	$(MYBIN)
				install -d $(BINPATH)/$(UTILSPATH)
				install -m 744 $(MYBIN) $(BINPATH)/$(UTILSPATH)
				$(TEST) || $(EXPR)
				$(RM) $(MYBIN)
				echo '#!/bin/bash' > $(BINPATH)/$(UTILSPATH)/uninstall.sh
				echo -n 'cat ~/.bashrc | grep '"'"'export PATH="$$PATH:$(BINPATH)/$(UTILSPATH)"'"'" >> $(UNINSTALL)
				echo '&& sed -i ''/$(KEYWORD)/d'' $(HOME)/.bashrc || echo -n '>> $(UNINSTALL)
				echo 'rm -rf $(BINPATH)/$(UTILSPATH)' >> $(UNINSTALL)
				chmod 744 $(UNINSTALL)

uninstall	:	fclean
				rm -rf $(BINPATH)/$(UTILSPATH)
				$(TEST) && sed -i '/$(KEYWORD)/d' $(HOME)/.bashrc || echo -n

./PHONY		:	all re clean fclean install uninstall
