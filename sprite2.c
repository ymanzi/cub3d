/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:24:02 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/11 15:01:33 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		get_nbr_sprite(t_cube *cube)
{
	int y;
	int x;
	int n_sprite;

	y = 0;
	n_sprite = 0;
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (cube->map[y][x] == '2')
				n_sprite++;
			x++;
		}
		y++;
	}
	cube->nbr_sprite = n_sprite;
	return (n_sprite);
}

int		get_coord_sprite(t_cube *cube)
{
	int y;
	int x;
	int nbr;

	y = 0;
	get_nbr_sprite(cube);
	if (!(cube->lst_sprite = (t_sprite*)
				malloc(sizeof(t_sprite) * cube->nbr_sprite)))
		return (free_cube_c(cube, 0));
	nbr = cube->nbr_sprite - 1;
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (cube->map[y][x] == '2')
			{
				cube->lst_sprite[nbr].x = y + 0.5;
				cube->lst_sprite[nbr--].y = x + 0.5;
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	sprite_distance(t_cube *cube)
{
	int nbr;
	int i;

	i = 0;
	nbr = cube->nbr_sprite;
	while ((nbr - i) > 0)
	{
		cube->lst_sprite[i].distance = (double)((cube->pos_x -
			cube->lst_sprite[i].x) *
	(cube->pos_x - cube->lst_sprite[i].x) + (cube->pos_y - cube->
		lst_sprite[i].y) * (cube->pos_y - cube->lst_sprite[i].y));
		i++;
	}
}

void	sprite_swipt(t_sprite *one, t_sprite *two)
{
	double	inter_x;
	double	inter_y;
	double	inter_distance;

	inter_x = one->x;
	inter_y = one->y;
	inter_distance = one->distance;
	one->x = two->x;
	one->y = two->y;
	one->distance = two->distance;
	two->x = inter_x;
	two->y = inter_y;
	two->distance = inter_distance;
}

void	sort_sprite(t_cube *cube)
{
	int		i;
	int		k;
	int		j_max;
	int		nbr;
	double	max_distance;

	i = -1;
	j_max = 0;
	nbr = cube->nbr_sprite;
	sprite_distance(cube);
	while (++i < nbr)
	{
		j_max = i;
		k = i;
		max_distance = cube->lst_sprite[i].distance;
		while (++k < nbr)
		{
			if (cube->lst_sprite[k].distance > max_distance)
			{
				j_max = k;
				max_distance = cube->lst_sprite[k].distance;
			}
		}
		sprite_swipt(&cube->lst_sprite[i], &cube->lst_sprite[j_max]);
	}
}
