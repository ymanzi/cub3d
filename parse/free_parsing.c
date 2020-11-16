/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:32:40 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 17:21:36 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_parsing.h"

int		verif_coord(char one, char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == one || line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strlen(line + i) < 1)
		return (ft_error("Verifier R/F ou C aucune donnee"));
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' ||
				(line[i] >= '0' && line[i] <= '9') || line[i] == ',')
			i++;
		else
			return (ft_error("Verifier R/F ou C donnee invalide"));
	}
	return (1);
}

void	free_cube(t_parsing *cube)
{
	int i;

	i = 0;
	if (cube)
	{
		if (cube->north)
			free(cube->north);
		if (cube->south)
			free(cube->south);
		if (cube->west)
			free(cube->west);
		if (cube->east)
			free(cube->east);
		if (cube->sprite)
			free(cube->sprite);
		if (cube->map)
			free(cube->map);
	}
}

int		fct_free(t_parsing *cube, char **line, char **str_no_space)
{
	free_cube(cube);
	if (*line)
		free(*line);
	if (*str_no_space)
		free(*str_no_space);
	return (0);
}

char	*free_gestion(char **no_space, char **str_no_space)
{
	if (*no_space)
	{
		free(*no_space);
		*no_space = NULL;
	}
	if (*str_no_space)
	{
		free(*str_no_space);
		*str_no_space = NULL;
	}
	return (NULL);
}
