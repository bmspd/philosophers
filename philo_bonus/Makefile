SRCS	= atoi.c extra_foo.c main.c initions.c time.c sema_print.c \
			philo.c

OBJS	= $(SRCS:.c=.o)

HEADER			= philosopher.h
CC				= gcc
RM				= rm -f
#CFLAGS			= -Wall -Werror -Wextra -I $(HEADER)
CFLAGS			= -I $(HEADER)
NAME			= philo_bonus


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