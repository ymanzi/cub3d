/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:56:55 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 16:45:39 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
** KEY_UP 126
** KEY_DOWN 125
** KEY_RIGHT 124
** KEY_LEFT 123
** KEY_ESC  53
*/

void	key_w_s(int keycode, t_cube *cube)
{
	double movespeed;

	movespeed = 0.2;
	if (keycode == KEY_W)
	{
		if (!((int)(cube->map[(int)(cube->pos_x +
				cube->dir_x * movespeed)][(int)(cube->pos_y)]) - 48))
			cube->pos_x += cube->dir_x * movespeed;
		if (!((int)(cube->map[(int)(cube->pos_x)][(int)(cube->pos_y
				+ cube->dir_y * movespeed)]) - 48))
			cube->pos_y += cube->dir_y * movespeed;
	}
	else if (keycode == KEY_S)
	{
		if (!((int)(cube->map[(int)(cube->pos_x -
			cube->dir_x * movespeed)][(int)(cube->pos_y)]) - 48))
			cube->pos_x -= cube->dir_x * movespeed;
		if (!((int)(cube->map[(int)(cube->pos_x)][(int)(cube->pos_y
			- cube->dir_y * movespeed)]) - 48))
			cube->pos_y -= cube->dir_y * movespeed;
	}
	draw_frame(cube);
}

void	key_a_d(int keycode, t_cube *cube)
{
	double movespeed;

	movespeed = 0.1;
	if (keycode == KEY_D)
	{
		if (!((int)(cube->map[(int)(cube->pos_x + cube->dir_y
							* movespeed)][(int)(cube->pos_y)]) - 48))
			cube->pos_x += cube->dir_y * movespeed;
		if (!((int)(cube->map[(int)(cube->pos_x)][(int)(cube->pos_y
							- cube->dir_x * movespeed)]) - 48))
			cube->pos_y -= cube->dir_x * movespeed;
	}
	else if (keycode == KEY_A)
	{
		if (!((int)(cube->map[(int)(cube->pos_x - cube->dir_y
							* movespeed)][(int)(cube->pos_y)]) - 48))
			cube->pos_x -= cube->dir_y * movespeed;
		if (!((int)(cube->map[(int)(cube->pos_x)][(int)(cube->pos_y
							+ cube->dir_x * movespeed)]) - 48))
			cube->pos_y += cube->dir_x * movespeed;
	}
	draw_frame(cube);
}

void	key_left_right(int keycode, t_cube *cube)
{
	double	olddir_x;
	double	oldplane_x;
	double	rot_s;

	olddir_x = cube->dir_x;
	oldplane_x = cube->plane_x;
	rot_s = 0.2;
	if (keycode == KEY_RIGHT)
	{
		cube->dir_x = cube->dir_x * cos(-rot_s) - cube->dir_y * sin(-rot_s);
		cube->dir_y = olddir_x * sin(-rot_s) + cube->dir_y * cos(-rot_s);
		cube->plane_x = cube->plane_x * cos(-rot_s)
			- cube->plane_y * sin(-rot_s);
		cube->plane_y = oldplane_x * sin(-rot_s) + cube->plane_y * cos(-rot_s);
	}
	else if (keycode == KEY_LEFT)
	{
		cube->dir_x = cube->dir_x * cos(rot_s) - cube->dir_y * sin(rot_s);
		cube->dir_y = olddir_x * sin(rot_s) + cube->dir_y * cos(rot_s);
		cube->plane_x = cube->plane_x * cos(rot_s)
			- cube->plane_y * sin(rot_s);
		cube->plane_y = oldplane_x * sin(rot_s) + cube->plane_y * cos(rot_s);
	}
	draw_frame(cube);
}

int		key_hook(int keycode, t_cube *cube)
{
	mlx_clear_window(cube->mlx, cube->window);
	if (keycode == KEY_W || keycode == KEY_S)
		key_w_s(keycode, cube);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_left_right(keycode, cube);
	else if (keycode == KEY_A || keycode == KEY_D)
		key_a_d(keycode, cube);
	else if (keycode == 53)
		return (free_cube_c(cube, 0));
	else
		draw_frame(cube);
	return (1);
}
