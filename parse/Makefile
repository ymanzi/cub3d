# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 14:05:13 by ymanzi            #+#    #+#              #
#    Updated: 2020/02/19 13:33:37 by ymanzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = cube_parsing.c cube_parsing2.c free_parsing.c ft_strdup_cube.c return_error.c
LFT_SRC = libft
LFT = $(LFT_SRC)/libft.a

OBJ = $(SRCS:.c=.o)

all: $(LFT) $(NAME)

$(NAME): $(OBJ)
		cp $(LFT_SRC)/libft.a $(NAME)
		ar rc $(NAME) $(OBJ)
$(LFT):
		(cd $(LFT_SRC) && $(MAKE))
clean:
		rm -f $(OBJ) 
		(cd $(LFT_SRC) && $(MAKE) $@)
fclean: clean
		rm -f $(NAME)
		(cd $(LFT_SRC) && $(MAKE) $@)
re: fclean all

.PHONY:all fclean re clean
