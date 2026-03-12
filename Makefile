NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

SRC = codexion.c initializer.c initializer_utils.c logic.c \
	logic_utils.c logic_utils2.c parser.c


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME) $(BNAME)

re : fclean all

.PHONY: all clean fclean re
