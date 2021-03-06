NAME = libprintf.a
SRCS = ori_printf.c atoi_count.c number.c putnbr_base.c p_put.c c_put.c per_put.c s_put.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c -I ori_printf.h

all:	$(NAME)

re:		fclean all

fclean:	clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

$(NAME):	$(OBJS)
	ar -rc $@ $^

.c.o:
	$(CC) $(CFLAGS) $^

