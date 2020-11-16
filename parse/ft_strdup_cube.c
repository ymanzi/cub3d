/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:08:27 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 15:58:59 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_parsing.h"

char		*ft_strdup_cube(char *s)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (i + 1))))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			ptr[i] = '0';
		else
			ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	free(s);
	return (ptr);
}

static int	boucle_map_1(char *s, int *i_x_y, int *taille)
{
	if (taille[0])
	{
		if (i_x_y[1] != taille[0])
			return (ft_error("La Map n'est pas rectangulaire"));
	}
	else
		taille[0] = i_x_y[1];
	i_x_y[2]++;
	if (s[i_x_y[0] + 1])
		i_x_y[1] = -1;
	return (1);
}

static int	boucle_map_2(t_parsing *cube, char *s, int *i_x_y, int *taille)
{
	if (s[i_x_y[0]] == 'N' || s[i_x_y[0]] == 'S'
			|| s[i_x_y[0]] == 'E' || s[i_x_y[0]] == 'W')
	{
		taille[1]++;
		cube->dir = s[i_x_y[0]];
		cube->px = i_x_y[1];
		cube->py = i_x_y[2];
	}
	else if (s[i_x_y[0]] < '0' || s[i_x_y[0]] > '9')
		return (ft_error("Map erronee"));
	return (1);
}

int			taille_map(t_parsing *cube, char *s)
{
	int i_x_y[3];
	int taille[2];

	bzero(taille, 2 * sizeof(int));
	bzero(i_x_y, 3 * sizeof(int));
	i_x_y[0] = -1;
	i_x_y[1] = -1;
	while (s[++i_x_y[0]])
	{
		i_x_y[1]++;
		if (s[i_x_y[0]] == ' ')
		{
			if (!(boucle_map_1(s, i_x_y, taille)))
				return (0);
		}
		else
		{
			if (!(boucle_map_2(cube, s, i_x_y, taille)))
				return (0);
		}
	}
	cube->map_w = i_x_y[2];
	cube->map_h = taille[0];
	return ((taille[1] == 1) ? 1 : ft_error("Map Erronee"));
}

int			verif_rep(t_parsing *cube, int i)
{
	if (!cube->verif[i])
		cube->verif[i] = 1;
	else
		return (ft_error("Repetition de certains elements du parsing"));
	return (1);
}
