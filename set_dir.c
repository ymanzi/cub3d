/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:29:41 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 15:36:55 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_value_plane(t_cube *cube, double planex, double planey)
{
	cube->plane_x = planex;
	cube->plane_y = planey;
}

static void	set_value_dir(t_cube *cube, double dirx, double diry)
{
	cube->dir_x = dirx;
	cube->dir_y = diry;
}

void		set_dir(t_cube *cube, t_parsing *parse)
{
	if (parse->dir == 'N')
	{
		set_value_dir(cube, -1, 0);
		set_value_plane(cube, 0, 0.66);
	}
	else if (parse->dir == 'W')
	{
		set_value_dir(cube, 0, -1);
		set_value_plane(cube, -0.66, 0);
	}
	else if (parse->dir == 'S')
	{
		set_value_dir(cube, 1, 0);
		set_value_plane(cube, 0, -0.66);
	}
	else
	{
		set_value_dir(cube, 0, 1);
		set_value_plane(cube, 0.66, 0);
	}
}
