SRC =	main.c \
	core/connection.c \
	core/readline.c \
	core/runcmd.c \
	core/list.c \
	core/cmp.c \
	core/game.c \
	../../lib/my_nbrtostr.c \
	core/commands.c

NAME =	client
OBJO =	$(SRC:%.c=%.o)
OBJC =	$(SRC)
CFLAGS = -W -Werror -Wall

all:	$(NAME)

$(NAME):	$(OBJO)
	gcc -W -Werror -Wall $(OBJO) -o $(NAME) -L. -lmy

clean:
	rm -f $(OBJO)
fclean:		clean
	rm -f $(NAME)

re:	fclean all
