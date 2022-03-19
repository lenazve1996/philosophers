NAME		= philo_bonus
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address 
SRC			= ../philo/libft/ft_atoi.c ../philo/libft/ft_strlen.c ../philo/libft/ft_isdigit_orsign.c \
				../philo/libft/ft_putstr_ret.c ../philo/parser.c main_bonus.c
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