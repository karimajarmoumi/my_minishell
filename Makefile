NAME = minishell
HOME_BREW_PATH=/Users/kel-baam/Desktop/homebrew
CC = cc
RFLAG = -L ${HOME_BREW_PATH}/opt/readline/lib -I ${HOME_BREW_PATH}/opt/readline/include -lreadline

CFLAGS = -g -fsanitize=address    -Wall -Wextra -Werror

SUB = *.c ./executer/*.c ./parser/*.c ./utils/*.c ./executer/builtins/*.c

OBJ =  *.o ./executer/*.o ./parser/*.o ./utils/*.o ./executer/builtins/*.o


all : $(NAME)

$(NAME) :$(SUB)
	${CC} ${SUB} ${CFLAGS}  -o ${NAME} ${RFLAG} -lreadline


clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
