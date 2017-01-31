SRC =	main.c \
	core/util.c \
	core/log.c \
	core/network/client.c \
	core/network/game.c \
	../lib/list.c \
	../lib/memset.c \
	../lib/my_nbrtostr.c

NAME =	bomberman
OBJO =	$(SRC:%.c=%.o)
OBJC =	$(SRC)
CFLAGS = -W -Werror -Wall
CC = gcc

all:	$(NAME)

$(NAME):	$(OBJO)
	gcc -W -Werror -Wall $(OBJO) -o $(NAME) -L. -lmy

clean:
	rm -f $(OBJO)
fclean:		clean
	rm -f $(NAME)

re:	fclean all
