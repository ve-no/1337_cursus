# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 13:37:46 by ael-bako          #+#    #+#              #
#    Updated: 2022/10/24 12:06:19 by ael-bako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=libft.a
CFLAGS=-Wall -Wextra -Werror

SRC= ft_atoi.c ft_isalpha.c ft_putchar_fd.c ft_strchr.c ft_tolower.c ft_strnstr.c \
	ft_bzero.c ft_isascii.c ft_memcpy.c ft_putendl_fd.c ft_strlen.c ft_toupper.c \
	ft_calloc.c ft_isdigit.c ft_memmove.c ft_putnbr_fd.c ft_strrchr.c ft_strncmp.c \
	ft_isalnum.c ft_isprint.c ft_memset.c ft_putstr_fd.c ft_substr.c ft_strjoin.c \
	ft_memchr.c ft_memcmp.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_itoa.c \
	ft_striteri.c ft_strmapi.c ft_split.c ft_strtrim.c \

OBJ=$(SRC:.c=.o)

BONUS= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstiter_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstlast_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c \

BOBJ=$(BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME) $(BOBJ)
	ar -crs $(NAME) $(BOBJ)
