CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

HDR = philo.h

SRC = philo.c\
	parcing.c \
	philo_utils.c \
	routine.c 

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HDR)
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(OBJ) $(NAME)

re: fclean all