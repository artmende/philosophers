# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmende <artmende@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:20:49 by artmende          #+#    #+#              #
#    Updated: 2021/12/27 16:21:14 by artmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthreads

SRCS =  ./push_swap_folder/main.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
        $(CC) -o $(NAME) $(CFLAGS) $(OBJS)

clean:
        $(RM) $(OBJS)

fclean: clean
        $(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
