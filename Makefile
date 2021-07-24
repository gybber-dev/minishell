NAME		= minishell

SRCS	= src/main.c \
	src/builtins/builtins.c \
	src/builtins/ft_cd.c \
	src/builtins/ft_echo.c \
	src/builtins/ft_env.c \
	src/builtins/ft_exit.c \
	src/builtins/ft_export.c \
	src/builtins/ft_pwd.c \
	src/builtins/ft_unset.c \
	src/builtins/heredoc.c \
	src/builtins/tools.c \
	src/parser/check_valid.c \
	src/parser/parser.c

OBJS		= $(patsubst %.c, %.o, $(SRCS))

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
HEADER		= src/includes/minishell.h
RM			= rm -f
LIB_FLAGS	= -Llibmlx_mac -lmlx -framework OpenGL -framework AppKit


all:		${NAME}



#$(NAME):	$(OBJS) $(HEADER)
#			$(CC) $(FLAGS) ${OBJS} -Llibft -lft $(LIB_FLAGS) -o $(NAME)

$(NAME): $(HEADER) $(SRCS)
			make bonus -C libft
			gcc $(SRCS) $(FLAGS) -g -Llibft -lft -lreadline -L/Users/yeschall/.brew/opt/readline/lib -I/Users/yeschall/.brew/opt/readline/include -o $(NAME)
			#gcc $(SRCS)  -g -Llibft -lft -lreadline -L/Users/yeschall/.brew/opt/readline/lib -I/Users/yeschall/.brew/opt/readline/include -o $(NAME)

%.o : %.c
			${CC} $(FLAGS) -c $< -o $@

clean:
			${RM} ${OBJS} ${BOBJS} *.out
			make -C libft clean

fclean:		clean
			make -C libft fclean
			#$(RM) -f $(NAME)

re:			fclean all

norm:
			norminette $(SRCS)
			norminette $(HEADER)
			norminette libft/*.c

.PHONY:		all clean fclean re norm