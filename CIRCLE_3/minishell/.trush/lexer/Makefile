NAME = hello.out
CC			= gcc
# CFLAGS		= -Wall -Werror -Wextra
# SRCS = $(wildcard src/*.c)
SRCS = src/lexer.c  src/main.c src/token.c
LIBFT		= src/libft/libft.a

OBJS = $(SRCS:.c=.o)
flags = -Wall -Werror -Wextra


# $(NAME): $(OBJS)
# 	gcc $(OBJS) $(flags) -o $(NAME) -lreadline
# 	mv *.o ..

$(NAME): $(OBJS)
	@${MAKE} -C src/libft
	@$(CC)  -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@rm $(OBJS)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./hello.out /usr/local/bin/hello

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

