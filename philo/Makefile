SRCS	= atoi.c extra_foo.c main.c

OBJS	= $(SRCS:.c=.o)

HEADER			= philosopher.h
CC				= gcc
RM				= rm -f
#CFLAGS			= -Wall -Werror -Wextra -I $(HEADER)
CFLAGS			= -I $(HEADER)
NAME			= philo


all:			 $(NAME)


%.o:		%.c $(HEADER)
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re