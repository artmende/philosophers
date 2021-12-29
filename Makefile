# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmende <artmende@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:20:49 by artmende          #+#    #+#              #
#    Updated: 2021/12/29 14:34:26 by artmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS =	./main.c \
		./acquire_args.c \
		./init_create_join.c \
		./life_check.c \
		./thread_routines.c \
		./time_fct.c \
		./from_libft/ft_atoi.c \
		./from_libft/ft_strchr.c \

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
