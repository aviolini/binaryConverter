MYBINS		=	randomNum sizeof toBits toDec
PREFIX		=	doit_
WITHPREFIX	=	$(addprefix $(PREFIX), $(MYBINS))
SRCS		=	randomNum.c	sizeof.c toBits.c toDec.c
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
APPSDIR		=	DoItInConsole
BINDIR		=	$(HOME)/bin/$(APPSDIR)
KEYWORD		=	\#thisIsThe$(APPSDIR)BinPath
TEST		=	cat ~/.bashrc | grep 'export PATH="$$PATH:$(BINDIR)"'
EXPR		=	echo 'export PATH="$$PATH:$(BINDIR)" $(KEYWORD)'  >> $(HOME)/.bashrc
UNINSTALL	=	$(BINDIR)/uninstall-$(APPSDIR).sh

all			:	
				$(CC) $(CFLAGS) -o $(addprefix doit_, randomNum) randomNum.c
				$(CC) $(CFLAGS) -o $(addprefix doit_, sizeof) sizeof.c
				$(CC) $(CFLAGS) -o $(addprefix doit_, toBits) toBits.c
				$(CC) $(CFLAGS) -o $(addprefix doit_, toDec) toDec.c

clean		:
				$(RM) $(WITHPREFIX)

fclean		:	clean

re			:	fclean all

install		:	all
				mkdir -p $(BINDIR)
				mv $(WITHPREFIX)  $(BINDIR)/
				cp README.md $(BINDIR)/
				$(TEST) || $(EXPR)
				echo '#!/bin/bash' > $(UNINSTALL)
				echo -n 'cat ~/.bashrc | grep '"'"'export PATH="$$PATH:$(BINDIR)"'"'" >> $(UNINSTALL)
				echo '&& sed -i ''/$(KEYWORD)/d'' $(HOME)/.bashrc || echo -n '>> $(UNINSTALL)
				echo 'rm -rf $(BINDIR)' >> $(UNINSTALL)
				chmod 744 $(UNINSTALL)

uninstall	:	fclean
				rm -rf $(BINDIR)
				$(TEST) && sed -i '/$(KEYWORD)/d' $(HOME)/.bashrc || echo -n

./PHONY		:	all re clean fclean install uninstall
