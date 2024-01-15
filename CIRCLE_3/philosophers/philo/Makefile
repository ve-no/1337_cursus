# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 18:37:13 by ael-bako          #+#    #+#              #
#    Updated: 2023/04/04 15:59:00 by ael-bako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = 	src/main.c src/philo.c src/utils.c\

OBJS	=	$(SRCS:.c=.o)

all:  $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJS)
	gcc -lpthread $(OBJS)  -o $(NAME)
fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
