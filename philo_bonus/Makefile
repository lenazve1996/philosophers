NAME		= philo_bonus
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
SRC			= ../philo/libft/ft_atoi.c ../philo/libft/ft_strlen.c \
				../philo/libft/ft_isdigit_orsign.c \
				../philo/libft/ft_putstr_ret.c \
				time_bonus.c main_bonus.c actions_bonus.c monitoring_bonus.c parser_bonus.c
OBJ			= $(SRC:.c=.o)
D_FILES 	= $(SRC:.c=.d)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $@

%.o : %.c
		$(CC) $(FLAGS) -c $? -o $@ -MD

clean :
		rm -f $(OBJ) $(OBJ_BONUS)
		rm -f $(D_FILES)

fclean : clean
		rm -f $(NAME) $(BONUS)

re : fclean all

.PHONY: all clean fclean re bonus libmake