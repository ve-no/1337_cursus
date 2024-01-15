NAME	=	cub3D
RM		=	rm -f
CC		=	gcc -Iincludes -I libs/libft/includes #-g -fsanitize=address
MLXFLG	=	-Ofast -lmlx -framework OpenGL -framework AppKit
LIBFT	=	libft/libft.a
SRCS	=	src/main.c src/parsing/parsing.c src/parsing/check_map.c src/parsing/check_extension.c\
			 src/parsing/parsing_utils.c src/raycasting/raycast_1.c src/raycasting/raycast_2.c \
			 src/raycasting/raycast_utils.c src/raycasting/raycast.c src/raycasting/key_hook.c $(LIBFT)


all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) $(MLXFLG) $(SRCS) -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
