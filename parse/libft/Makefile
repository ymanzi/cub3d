# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 14:05:13 by ymanzi            #+#    #+#              #
#    Updated: 2020/02/17 14:04:13 by ymanzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRCS = ft_atoi.c ft_isalpha.c ft_memccpy.c ft_memmove.c ft_strlcat.c \
ft_strnstr.c ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_strlcpy.c \
ft_strrchr.c ft_calloc.c ft_isdigit.c ft_memcmp.c ft_strchr.c ft_strlen.c \
ft_tolower.c ft_isalnum.c ft_isprint.c ft_memcpy.c ft_strdup.c ft_strncmp.c \
ft_toupper.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c ft_strjoin.c
SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
GNL_SRC = gnl
GNL = $(GNL_SRC)/gnl.a
OBJ = $(SRCS:.c=.o)
OBJ_B = $(SRCS_B:.c=.o)

all: $(GNL) $(NAME)

$(NAME): $(OBJ)
		cp $(GNL_SRC)/gnl.a $(NAME)
		ar rc $(NAME) $(OBJ)
$(GNL):
		(cd $(GNL_SRC) && $(MAKE))
bonus: all $(OBJ_B)
		ar rc $(NAME) $(OBJ_B)
clean:
		rm -f $(OBJ) $(OBJ_B)
		(cd $(GNL_SRC) && $(MAKE) $@)
fclean: clean
		rm -f $(NAME)
		(cd $(GNL_SRC) && $(MAKE) $@)
re: fclean all
