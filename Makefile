SRC= $(wildcard *.c)
OBJ=$(SRC:.c=.o)
NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread
${philo}: all

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)