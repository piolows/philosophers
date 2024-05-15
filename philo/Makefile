NAME = philo
SRCS = main.c time.c parsing.c init_data.c init_mutexes.c threads.c \
			check_forks.c take_forks.c monitor.c print.c utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re