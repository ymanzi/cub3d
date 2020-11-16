# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/17 13:36:52 by ymanzi            #+#    #+#              #
#    Updated: 2020/02/19 17:39:58 by ymanzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOM=cube3d.a
SRC= main.c algo.c algo_orientation.c bmp.c dessin.c init.c keys_fct.c set_dir.c sprite.c sprite2.c global.c
PARSE_SRC = parse
MLX_SRC = mlx
PARSE = $(PARSE_SRC)/parse.a
OBJ=$(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(PARSE) $(NOM)

$(NOM):	$(OBJ)
	cp $(PARSE_SRC)/parse.a $(NOM)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)
$(PARSE):
	(cd $(PARSE_SRC) && $(MAKE))
	(cd $(MLX_SRC) && $(MAKE))
gen:
	gcc -Wall -Wextra -Werror cube3d.a $(MLX_SRC)/libmlx.a -framework OpenGL -framework AppKit -o cub3D main.c

bonus: all

clean:
	rm -f $(OBJ) *~
	rm -f mlx_app
	(cd $(PARSE_SRC) && $(MAKE) $@)
	(cd $(MLX_SRC) && $(MAKE) $@)
fclean: clean
	rm -f $(NOM)
	(cd $(PARSE_SRC) && $(MAKE) $@)
	(cd $(MLX_SRC) && $(MAKE) $@)
re: fclean all
