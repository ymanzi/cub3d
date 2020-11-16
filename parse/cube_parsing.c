/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:15:13 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 17:18:47 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_parsing.h"

static int	init_data_nswe(t_parsing *cube, char *line)
{
	int ret;

	ret = 0;
	if (line[0] == 'N' && line[1] == 'O' && verif_rep(cube, 0))
		ret = set_data_nswe(&cube->north, line);
	else if (line[0] == 'S' && line[1] == 'O' && verif_rep(cube, 1))
		ret = set_data_nswe(&cube->south, line);
	else if (line[0] == 'W' && line[1] == 'E' && verif_rep(cube, 2))
		ret = set_data_nswe(&cube->west, line);
	else if (line[0] == 'E' && line[1] == 'A' && verif_rep(cube, 3))
		ret = set_data_nswe(&cube->east, line);
	else if (line[0] == 'S' && !line[1])
		return (ft_error("Path Sprite erronee"));
	else if (line[0] == 'S' && line[1] != 'O' && verif_rep(cube, 4))
		ret = set_data_nswe(&cube->sprite, line);
	else
		return (ft_error("Donne de Texture erronee"));
	return (ret);
}

static int	init_data_r_rgb(t_parsing *cube, char *line)
{
	if (line[0] == 'R' && verif_rep(cube, 5))
	{
		while ((*line < '0' || *line > '9') && *line != '-')
			line++;
		cube->x = ft_atoi(line);
		if (*line == '-')
			line++;
		while (*line >= '0' && *line <= '9')
			line++;
		cube->y = ft_atoi(line);
	}
	else if (line[0] == 'F' && verif_rep(cube, 6))
		set_data_rgb(&cube->sol_r, &cube->sol_g, &cube->sol_b, line);
	else if (line[0] == 'C' && verif_rep(cube, 7))
		set_data_rgb(&cube->plafond_r,
				&cube->plafond_g, &cube->plafond_b, line);
	else
		return (0);
	if (!(verif_coord(line[0], line)))
		return (0);
	return (1);
}

static char	*parse_map(char **line, char **str_no_space)
{
	char		*new_str;
	char		*no_space;
	char		*no_debut;
	static int	taille = 0;

	no_debut = del_debutspace(*line);
	if (!(no_space = del_allspace(no_debut)))
		return (free_gestion(&no_space, str_no_space));
	if (!taille)
		taille = ft_strlen(no_space);
	else
	{
		if (taille != (int)ft_strlen(no_space))
		{
			ft_error("La Map n'est pas rectangulaire");
			return (free_gestion(&no_space, str_no_space));
		}
	}
	if (!(no_space = ft_strjoin(no_space, " ")))
		return (free_gestion(&no_space, str_no_space));
	if (!(new_str = ft_strjoin(*str_no_space, no_space)))
		return (free_gestion(&no_space, str_no_space));
	free(no_space);
	return (new_str);
}

static char	*gestion_line(t_parsing *cube, char **line, char **str_no_space)
{
	char	*no_debut;

	no_debut = del_debutspace(*line);
	if (*no_debut)
	{
		if (no_debut[0] == '1' || no_debut[0] == '0')
		{
			cube->verif[8] = 1;
			return (parse_map(line, str_no_space));
		}
		else
		{
			if (no_debut[0] == 'R' || no_debut[0] == 'F' || no_debut[0] == 'C')
			{
				if (!(init_data_r_rgb(cube, no_debut)))
					return (NULL);
			}
			else if (!(init_data_nswe(cube, no_debut)))
				return (NULL);
		}
	}
	else if (cube->verif[8])
		return (ft_error_str("La map est erronee"));
	return (*str_no_space);
}

int			get_parsing(t_parsing *cube, int fd)
{
	char		*line;
	char		*str_no_space;
	int			ret;

	ft_bzero(cube, sizeof(*cube));
	if (!(str_no_space = ft_strdup("")))
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(str_no_space = gestion_line(cube, &line, &str_no_space)))
			return (fct_free(cube, &line, &str_no_space));
		free(line);
	}
	if (ret == -1)
		return (fct_free(cube, &line, &str_no_space));
	if (!(taille_map(cube, str_no_space)))
		return (fct_free(cube, &line, &str_no_space));
	if (!(str_no_space = ft_strdup_cube(str_no_space)))
		return (fct_free(cube, &line, &str_no_space));
	if (!(cube->map = ft_strdup(str_no_space)) || !verif_parsing(cube))
		return (fct_free(cube, &line, &str_no_space));
	close(fd);
	fct_free(0, &line, &str_no_space);
	return (1);
}
