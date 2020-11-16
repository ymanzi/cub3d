/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:17:45 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 16:56:49 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_parsing.h"

int			ft_error(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

char		*ft_error_str(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	return (NULL);
}

static int	v_map(t_parsing *cube)
{
	int tab[2];

	ft_bzero(tab, sizeof(tab));
	while (tab[0] < cube->map_w)
	{
		tab[1] = 0;
		while (tab[1] < cube->map_h + 1)
		{
			if ((tab[0] == 0 || tab[0] == cube->map_w - 1 || tab[1] == 0 ||
						tab[1] == cube->map_h - 1) && !(cube->map[tab[0] *
							(cube->map_h + 1) + tab[1]] - 48))
				return (ft_error("La Map est ouverte"));
			tab[1]++;
		}
		tab[0]++;
	}
	return (1);
}

int			verif_parsing(t_parsing *cube)
{
	int	i;

	i = -1;
	if (!cube->north || !cube->south || !cube->west || !cube->east
			|| !cube->sprite)
		return (ft_error("L'une des textures non-initialisee"));
	else if (!cube->dir)
		return (ft_error("Direction initial non initialisee"));
	else if (!cube->map_h || !cube->map_w)
		return (ft_error("Map invalide"));
	else if (cube->x <= 0 || cube->y <= 0)
		return (ft_error("Mauvaise resolution d'ecran"));
	if (!v_map(cube))
		return (0);
	while (++i < 9)
		if (!cube->verif[i])
			return (ft_error("Donnee de parsing manquant"));
	if (cube->x > 1080)
		cube->x = 1080;
	if (cube->y > 720)
		cube->y = 720;
	return (1);
}
