# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 11:20:00 by ael-bako          #+#    #+#              #
#    Updated: 2022/10/31 14:39:02 by ael-bako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=libftprintf.a
CFLAGS=-Wall -Wextra -Werror

SRC= ft_printhex.c ft_printunsigned.c ft_utils.c \
	ft_printptr.c  ft_printf.c ft_itoa.c ft_putchar_fd.c\

OBJ=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
