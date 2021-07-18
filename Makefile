SRC		=	srcs/main.c \
			srcs/utils.c \
			srcs/monitor.c \
			srcs/philo_cycle.c \
			srcs/otherstuff.c

BONUS	=	philo_bonus/main.c \
			philo_bonus/utils.c \
			philo_bonus/monitor.c \
			philo_bonus/philo_cycle.c \
			philo_bonus/otherstuff.c

NAME	=	philosophers
BONUSNAME = philosophers_bonus

OBJ		=	$(SRC:.c=.o)

OBONUS	=	$(BONUS:.c=.o)

FLAGS	=	-Wall -Werror -Wextra


all:		$(NAME)

bonus: $(NAME) $(BONUSNAME)

$(BONUSNAME): $(OBONUS)
	gcc $(OBONUS) -o $(BONUSNAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ) $(OBONUS) $(BONUSNAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re