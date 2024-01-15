NAME	=	minishell
RM		=	rm -f
DIR_SRCS	= src
CC		=	gcc -Wall -Wextra -Werror -Iincludes -I libft/includes
RLFLG	=	-lreadline -L /goinfre/ibouchaf/homebrew/opt/readline/lib -I /goinfre/ibouchaf/homebrew/opt/readline/include
LIBFT	=	libft/libft.a
SUBDIRS	=	builtins parser execution
SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))

SRCS	=	$(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c)) main.c $(LIBFT)

INCLUDES	= -I inc

all: $(NAME)

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libft

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) -g $(RLFLG) $(SRCS) -o $(NAME) $(INCLUDES)
	@echo "\033[1;32mMinishell has been compiled!\033[0m\n"

bonus: $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
