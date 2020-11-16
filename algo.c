/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:02:47 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 16:47:19 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_calcul_cube(t_cube *cube, int x)
{
	cube->cam_x = (double)(2 * x / (double)(cube->largeur) - 1);
	cube->ray_dir_x = cube->dir_x + cube->plane_x * cube->cam_x;
	cube->ray_dir_y = cube->dir_y + cube->plane_y * cube->cam_x;
	cube->map_x = (int)(cube->pos_x);
	cube->map_y = (int)(cube->pos_y);
	cube->delta_dist_x = fabs(1 / cube->ray_dir_x);
	cube->delta_dist_y = fabs(1 / cube->ray_dir_y);
}

void	calcul_raydir(t_cube *cube)
{
	if (cube->ray_dir_x < 0)
	{
		cube->step_x = -1;
		cube->side_dist_x = (cube->pos_x - cube->map_x) * cube->delta_dist_x;
	}
	else
	{
		cube->step_x = 1;
		cube->side_dist_x = (cube->map_x + 1.0 -
				cube->pos_x) * cube->delta_dist_x;
	}
	if (cube->ray_dir_y < 0)
	{
		cube->step_y = -1;
		cube->side_dist_y = (cube->pos_y -
				cube->map_y) * cube->delta_dist_y;
	}
	else
	{
		cube->step_y = 1;
		cube->side_dist_y = (cube->map_y + 1.0
				- cube->pos_y) * cube->delta_dist_y;
	}
}

void	calcul_distance(t_cube *cube)
{
	cube->hit = 0;
	while (cube->hit == 0)
	{
		if (cube->side_dist_x < cube->side_dist_y)
		{
			cube->side_dist_x += cube->delta_dist_x;
			cube->map_x += cube->step_x;
			cube->side = 0;
		}
		else
		{
			cube->side_dist_y += cube->delta_dist_y;
			cube->map_y += cube->step_y;
			cube->side = 1;
		}
		if (cube->map[cube->map_x][cube->map_y] == '1')
			cube->hit = 1;
	}
	if (cube->side == 0)
		cube->perp_wall_dist = (cube->map_x - cube->pos_x
				+ (1 - cube->step_x) / 2) / cube->ray_dir_x;
	else
		cube->perp_wall_dist = (cube->map_y - cube->pos_y
				+ (1 - cube->step_y) / 2) / cube->ray_dir_y;
}

void	calcul_collision_texture(t_cube *cube)
{
	if (cube->side == 0)
		cube->wall_x = cube->pos_y + cube->perp_wall_dist * cube->ray_dir_y;
	else
		cube->wall_x = cube->pos_x + cube->perp_wall_dist * cube->ray_dir_x;
	cube->wall_x -= floor(cube->wall_x);
	cube->tex_x = (int)(cube->wall_x * (double)TEXTURE_L);
	if (cube->side == 0 && cube->ray_dir_x > 0)
		cube->tex_x = TEXTURE_L - cube->tex_x - 1;
	if (cube->side == 1 && cube->ray_dir_y < 0)
		cube->tex_x = TEXTURE_L - cube->tex_x - 1;
}
