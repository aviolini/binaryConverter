MYBINS		=	ToBits ToDec
PREFIX		=	converter
WITHPREFIX	=	$(addprefix $(PREFIX), $(MYBINS))
SRCS		=	toBits.c toDec.c
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
APPSDIR		=	binaryConverter
BINDIR		=	$(HOME)/bin/$(APPSDIR)
KEYWORD		=	\#thisIsThe$(APPSDIR)BinPath
TEST		=	@cat ~/.bashrc | grep 'export PATH="$$PATH:$(BINDIR)"'
EXPR		=	echo 'export PATH="$$PATH:$(BINDIR)" $(KEYWORD)'  >> $(HOME)/.bashrc
UNINSTALL	=	$(BINDIR)/uninstall-$(APPSDIR).sh

NONE	=	\e[0m
GREY	=	\e[0;37m
GREEN	=	\e[0;32m
YELLOW	=	\e[1;33m
BLUE	=	\e[0;36m
RED		=	\e[0;35m

help		:
				@printf "make ─┐\n"
				@printf "      ├─┐ $(YELLOW)#build locally (the apps can be called only from the project folder)$(NONE)\n"				
				@printf "      │ ├─all:   make binaries in the project dir\n"
				@printf "      │ └─clean: remove binaries from the project dir\n"
				@printf "      │\n"
				@printf "      └─┐ $(YELLOW)#build in system (the apps can be called everywhere - only for GNU/Linux system with bash)$(NONE)\n"
				@printf "        ├─install:   make binaries in the ~/bin/binaryConverter dir\n"
				@printf "        └─uninstall: uninstall binaries and remove ~/bin/binaryConverter dir\n"

all			:	
				$(CC) $(CFLAGS) -o $(addprefix $(PREFIX), ToBits) toBits.c
				$(CC) $(CFLAGS) -o $(addprefix $(PREFIX), ToDec) toDec.c

clean		:
				$(RM) $(WITHPREFIX)

install		:	all
				@mkdir -p $(BINDIR)
				@mv $(WITHPREFIX)  $(BINDIR)/
				@cp README.md $(BINDIR)/
				@$(TEST) || $(EXPR)
				@echo '#!/bin/bash' > $(UNINSTALL)
				@echo -n 'cat ~/.bashrc | grep '"'"'export PATH="$$PATH:$(BINDIR)"'"'" >> $(UNINSTALL)
				@echo '&& sed -i ''/$(KEYWORD)/d'' $(HOME)/.bashrc || echo -n '>> $(UNINSTALL)
				@echo 'rm -rf $(BINDIR)' >> $(UNINSTALL)
				@chmod 744 $(UNINSTALL)
				@printf "$(GREEN)succesfully installed!$(NONE)\n"
				@printf "run 'source ~/.bashrc' from your console to reload bash\n"

uninstall	:
				@rm -rf $(BINDIR)
				@$(TEST) && sed -i '/$(KEYWORD)/d' $(HOME)/.bashrc || echo -n
				@printf "$(GREEN)succesfully disinstalled!$(NONE)\n"


./PHONY		:	all re clean fclean install uninstall
