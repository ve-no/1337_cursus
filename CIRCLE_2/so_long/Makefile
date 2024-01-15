NAME		= so_long
NAME_B		= so_long_b
LIBFT		= libft/libft.a
INCLUDES	= -I inc
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
MLX 		= -g -lmlx -framework OpenGL -framework AppKit
OBJ_PATH 	= obj/
OBJ_PATH_B	= obj_b/
SRC_PATH	= src/
SRC_PATH_B	= bonus/

GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

SRC = map.c map_utils.c utils.c so_long.c
SRC_B = main.c map.c map_utils.c utils.c so_long.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
SRCS_B	= $(addprefix $(SRC_PATH_B), $(SRC_B))
OBJ		= $(SRC:.c=.o)
OBJ_B	= $(SRC_B:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
OBJS_B	= $(addprefix $(OBJ_PATH_B), $(OBJ_B))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "$(GREEN)Generating libft objects... %-500.900s\r" $@

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "$(WHT)Compiling libraries...$(EOC)"
	@${MAKE} -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${MLX} $(LIBFT)
	@echo "$(GREEN)Libraries done.$(EOC)"
	@echo "$(WHT)Compiling so_long...$(EOC)"
	@echo "$(GREEN)so_long build completed.$(EOC)"

bonus: $(OBJ_PATH_B) $(NAME_B)

$(OBJ_PATH_B)%.o: $(SRC_PATH_B)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "$(GREEN)Generating libft objects... %-500.900s\r" $@

$(OBJ_PATH_B):
	@mkdir $(OBJ_PATH_B)

$(NAME_B): $(OBJS_B)
	@echo "$(WHT)Compiling libraries...$(EOC)"
	@${MAKE} -C libft
	@$(CC) $(CFLAGS) -o $(NAME_B) $(OBJS_B) ${MLX} $(LIBFT)
	@echo "$(GREEN)Libraries done.$(EOC)"
	@echo "$(WHT)Compiling so_long...$(EOC)"
	@echo "$(GREEN)so_long build completed.$(EOC)"

clean:
	@/bin/rm -rf $(OBJ_PATH) $(OBJ_PATH_B)
	@/bin/rm -Rf obj
	@${MAKE} -C libft clean
	@echo "$(GREEN)Clean done.$(EOC)"

fclean: clean
	@/bin/rm -f $(NAME) $(NAME_B)
	@${MAKE} -C libft fclean
	@echo "$(GREEN)Fclean done.$(EOC)"

re: fclean all

.PHONY: all clean fclean re
