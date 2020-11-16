/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:45:27 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 16:04:14 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUBE_PARSING_H
#	define CUBE_PARSING_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/gnl/get_next_line.h"
#include "libft/libft.h"

typedef	struct	s_parsing
{
	int		x;
	int		y;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		sol_r;
	int		sol_g;
	int		sol_b;
	int		plafond_r;
	int		plafond_g;
	int		plafond_b;
	int		px;
	int		py;
	char	dir;
	char	*map;
	int		map_h;
	int		map_w;
	int		verif[9];
}				t_parsing;
/*
** ft_strdup_cube(t_parsing *cube, char *str)
*/

char			*ft_strdup_cube(char *s);
int				taille_map(t_parsing *cube, char *s);
int				verif_rep(t_parsing *cube, int i);
/*
** free_parsing.c
*/
int				verif_coord(char one, char *line);
void			free_cube(t_parsing *cube);
int				fct_free(t_parsing *cube, char **line, char **str_no_space);
char			*free_gestion(char **no_space, char **str_no_space);
/*
** return_error.c
*/
int				ft_error(char *str);
char			*ft_error_str(char *str);
int				verif_parsing(t_parsing *cube);
/*
** cube_parsing2.c
*/
int				ft_strlen_nospace(char *str);
char			*del_debutspace(char *str);
char			*del_allspace(char *str);
int				set_data_nswe(char **data, char *line);
void			set_data_rgb(int *data1, int *data2, int *data3, char *line);
/*
** cube_parsing.c
*/
int				get_parsing(t_parsing *cube, int fd);
#	endif
