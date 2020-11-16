/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:22:58 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/11 15:03:49 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#define TEXWIDTH 64
#define TEXHEIGHT 64

int			free_cube_c(t_cube *cube, int ret)
{
	int	i;

	i = 0;
	if (!cube->lst_sprite)
		free(cube->lst_sprite);
	if (!cube->sprite_buffer)
		free(cube->sprite_buffer);
	if (!cube->map)
	{
		while (cube->map[i])
		{
			free(cube->map[i]);
			i++;
		}
		free(cube->map);
	}
	mlx_destroy_image(cube->mlx, cube->img.img);
	mlx_destroy_window(cube->mlx, cube->window);
	if (!ret)
		exit(0);
	return (ret);
}

static void	init_data_sprite(t_cube *cube, int i)
{
	cube->sprite_x = cube->lst_sprite[i].x - cube->pos_x;
	cube->sprite_y = cube->lst_sprite[i].y - cube->pos_y;
	cube->inv_cam_matrix = (1.0 / (cube->plane_x *
				cube->dir_y - cube->dir_x * cube->plane_y));
	cube->trans_x = cube->inv_cam_matrix * (cube->dir_y *
			cube->sprite_x - cube->dir_x * cube->sprite_y);
	cube->trans_y = cube->inv_cam_matrix * (-cube->plane_y *
			cube->sprite_x + cube->plane_x * cube->sprite_y);
	cube->sprite_screen_x = (int)((cube->largeur / 2)
			* (1 + cube->trans_x / cube->trans_y));
	cube->sprite_height = abs((int)(cube->longueur / cube->trans_y));
	cube->draw_start_y = -cube->sprite_height / 2 + cube->longueur / 2;
	if (cube->draw_start_y < 0)
		cube->draw_start_y = 0;
	cube->draw_end_y = cube->sprite_height / 2 + cube->longueur / 2;
	if (cube->draw_end_y >= cube->longueur)
		cube->draw_end_y = cube->longueur - 1;
	cube->sprite_width = abs((int)(cube->longueur / cube->trans_y));
	cube->draw_start_x = -cube->sprite_width / 2 + cube->sprite_screen_x;
	if (cube->draw_start_x < 0)
		cube->draw_start_x = 0;
	cube->draw_end_x = cube->sprite_width / 2 + cube->sprite_screen_x;
	if (cube->draw_end_x >= cube->largeur)
		cube->draw_end_x = cube->largeur - 1;
}

static void	init_data_sprite2(t_cube *cube, int stripe)
{
	int	y;
	int	d;
	int	color;

	if (cube->trans_y > 0 && stripe > 0 && stripe < cube->largeur &&
			cube->trans_y < cube->sprite_buffer[stripe])
	{
		y = cube->draw_start_y - 1;
		while (++y < cube->draw_end_y)
		{
			d = (y) * 256 - cube->longueur * 128 + cube->sprite_height * 128;
			cube->tex_y = ((d * TEXHEIGHT) / cube->sprite_height) / 256;
			color = get_color_image(cube, cube->tex_x, cube->tex_y, 5);
			if ((color & 0xFFFFFF) != 0)
				my_mlx_pixel_put(cube, stripe, y, color);
		}
	}
}

int			init_sprite(t_cube *cube)
{
	int i;
	int	stripe;

	i = -1;
	if (!(get_coord_sprite(cube)))
		return (0);
	sort_sprite(cube);
	while (++i < cube->nbr_sprite)
	{
		init_data_sprite(cube, i);
		stripe = cube->draw_start_x - 1;
		while (++stripe < cube->draw_end_x)
		{
			cube->tex_x = (int)(256 * (stripe - (-cube->sprite_width / 2 +
				cube->sprite_screen_x)) * TEXWIDTH / cube->sprite_width) / 256;
			init_data_sprite2(cube, stripe);
		}
	}
	return (1);
}
