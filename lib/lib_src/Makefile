SRC =	lib/my_strncat.c \
	lib/my_strstr.c \
	lib/my_strcat.c \
	lib/my_putchar.c \
	lib/my_put_nbr.c \
	lib/my_swap.c \
	lib/my_strcpy.c \
	lib/my_getnbr.c \
	lib/my_putstr.c \
	lib/my_str_to_wordtab.c \
	lib/my_strdup.c \
	lib/my_strncpy.c \
	lib/my_strlen.c \
	lib/my_strncmp.c \
	lib/my_isneg.c \
	lib/my_strcmp.c \

NAME =	libmy
OBJO =	$(SRC:%.c=%.o)
OBJC =	$(SRC)
CFLAGS = -W -Werror -Wall
CC = gcc
 
all:	$(NAME)

$(NAME):	$(OBJO)
	ar rc $(NAME).a $(OBJO)
	ranlib $(NAME).a
clean:
	rm -f $(OBJO)
fclean:		clean
	rm -f $(NAME).a

re:	fclean all