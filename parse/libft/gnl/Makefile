# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 14:05:13 by ymanzi            #+#    #+#              #
#    Updated: 2020/02/17 14:04:35 by ymanzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=255
SRCS = get_next_line.c get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
clean:
		rm -f $(OBJ) 
fclean: clean
		rm -f $(NAME)
re: fclean all

.PHONY:all fclean re clean
