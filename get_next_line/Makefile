CC=cc
NAME=gnl.a
CFLAGS=-Wall -Wextra -Werror

SRC=get_next_line.c get_next_line_utils.c\

OBJ=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
