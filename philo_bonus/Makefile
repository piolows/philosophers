NAME = philo_bonus
SRCS = main_bonus.c parsing_bonus.c init_data_bonus.c processes_bonus.c \
			print_bonus.c time_bonus.c monitor_bonus.c utils_bonus.c
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