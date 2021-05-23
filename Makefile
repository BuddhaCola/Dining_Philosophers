SRC		=	srcs/main.c \
			srcs/ft_atoi.c

NAME	=	philo_one

OBJ		=	$(SRC:.c=.o)

FLAGS	=	#-Wall -Werror -Wextra

all:		$(NAME)

$(NAME): $(OBJ)
	gcc -g $(OBJ) -o $(NAME)

.c.o:
	gcc $(FLAGS) -g -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re