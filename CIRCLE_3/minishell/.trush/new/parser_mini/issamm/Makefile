NAME	= minishell

CC = gcc

SRCS = expand.c  params.c builtins/ft_pwd.c builtins/ft_exit.c builtins/ft_echo.c builtins/ft_cd.c builtins/ft_env.c builtins/ft_unset.c builtins/ft_export.c main.c fill_node.c ft_strtrim.c ft_cmdsubsplit.c parse_args.c utils.c

LIBFT		= libft/libft.a

CFLAGS 	= -Wextra -Werror -Wall

OBJS	= $(SRCS:.c=.o)

#  -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@${MAKE} -C libft
	$(CC) ${CFLAGS} -o $(NAME) $(OBJS) $(LIBFT) -lreadline -G
	@rm $(OBJS)

clean:
	@rm -f ${OBJS}


fclean:    clean
	@rm -f ${NAME}

re: fclean all
