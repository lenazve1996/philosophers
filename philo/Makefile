NAME		= philo
BONUS		= philo_bonus
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g
SRC			= libft/ft_atoi.c libft/ft_strlen.c libft/ft_isdigit_orsign.c \
				libft/ft_putstr_ret.c philo.c cleaning.c parser.c monitoring.c \
				main.c actions.c time.c
#SRC_BONUS	= 
OBJ			= $(SRC:.c=.o)
#OBJ_BONUS	= $(SRC_BONUS:.c=.o)
D_FILES 	= $(SRC:.c=.d) #$(SRC_BONUS:.c=.d)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $@

#bonus : $(BONUS)

#$(BONUS) : $(OBJ_BONUS)
#		$(CC) $(FLAGS) $(OBJ_BONUS) -o $@

%.o : %.c
		$(CC) $(FLAGS) -c $? -o $@ -MD

clean :
		rm -f $(OBJ) #$(OBJ_BONUS)
		rm -f $(D_FILES)

fclean : clean
		rm -f $(NAME) $(BONUS)

re : fclean all

.PHONY: all clean fclean re bonus libmake