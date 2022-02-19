NAME		= philo
BONUS		= checker
CC			= cc
FLAGS		= -Wall -Wextra -Werror
SRC			= 
SRC_BONUS	= 
OBJ			= $(SRC_:.c=.o)
OBJ_BONUS	= $(SRC_BONUS:.c=.o)
D_FILES 	= $(SRC:.c=.d) $(SRC_BONUS:.c=.d)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $@

bonus : $(BONUS)

$(BONUS) : $(OBJ_BONUS)
		$(CC) $(FLAGS) $(OBJ_BONUS) -o $@

%.o : %.c
		$(CC) $(FLAGS) -c $? -o $@ -MD

clean :
		rm -f $(OBJ) $(OBJ_BONUS)
		rm -f $(D_FILES)

fclean : clean
		rm -f $(NAME) $(BONUS)

re : fclean all

.PHONY: all clean fclean re bonus libmake