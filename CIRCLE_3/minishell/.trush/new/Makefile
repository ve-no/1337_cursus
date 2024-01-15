NAME = hello.out
CC			= gcc
# CFLAGS		= -Wall -Werror -Wextra
# SRCS = $(wildcard src/*.c)
SRCS = expand.c main.c fill_node.c ft_cmdtrim.c ft_cmdsubsplit.c parse_args.c utils.c ft_strtrim_all.c
LIBFT		= libft/bin/libft.a

OBJS = $(SRCS:.c=.o)
flags = -Wall -Werror -Wextra


# $(NAME): $(OBJS)
# 	gcc $(OBJS) $(flags) -o $(NAME) -lreadline
# 	mv *.o ..
%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

$(NAME): $(OBJS)
	${MAKE} -C libft
	$(CC)  -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@rm $(OBJS)

# -fsanitize=address -G

install:
	make
	cp ./hello.out /usr/local/bin/hello

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

