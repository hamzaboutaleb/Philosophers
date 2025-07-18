SRC= app.c \
	main.c \
	monitor.c \
	parse_args.c \
	philo_routine.c \
	philo.c \
	state.c \
	utils.c

OBJ=$(SRC:.c=.o)

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re