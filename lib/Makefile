NAME	=	libmy.a

RM	=	rm -f

CC	=	gcc

CFLAGS	=	-g3 -ggdb -W -Wall -Werror -ansi -pedantic -std=gnu99

SRCS	=	src/tab.c \
		src/my_puts.c \
		src/wordtab.c \
		src/megahal.c \

OBJS	=	$(SRCS:.c=.o)

ECHO	=	echo -e

all	:	$(NAME)

$(NAME)	:	$(OBJS)

		ar r $(NAME) $(OBJS)
		ranlib $(NAME)

clean	:

		$(RM) $(OBJS)

fclean	:	$(clean)
		$(RM) $(NAME)

re	:	fclean all

.PHONY	: all clean fclean re
