/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dessin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:06:49 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 17:02:00 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;

	dst = cube->img.addr + (y * cube->img.line_length
			+ x * (cube->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	verline(int x, int draw_start, int draw_end, t_cube *cube)
{
	int	hauteur;
	int	d;
	int	orientation;
	int color;

	hauteur = 0;
	while (hauteur < cube->longueur)
	{
		if (hauteur < draw_start)
			my_mlx_pixel_put(cube, x, hauteur++, cube->color_floor);
		else if (hauteur >= draw_start && hauteur <= draw_end)
		{
			d = hauteur * 256 - cube->longueur * 128 + cube->line_height * 128;
			cube->tex_y = ((d * TEXTURE_H) / cube->line_height) / 256;
			cube->tex_y = (cube->tex_y == 64 ? 63 : cube->tex_y);
			cube->tex_x = (cube->tex_x == 64 ? 63 : cube->tex_x);
			orientation = get_orientation(cube);
			if (orientation < 5)
				color = get_color_image(cube,
						cube->tex_x, cube->tex_y, orientation);
			my_mlx_pixel_put(cube, x, hauteur++, color);
		}
		else
			my_mlx_pixel_put(cube, x, hauteur++, cube->color_ceiling);
	}
}

void	gestion_dessin(t_cube *cube)
{
	int	h;

	h = cube->longueur;
	cube->line_height = (int)(h / cube->perp_wall_dist);
	cube->draw_start = -cube->line_height / 2 + h / 2;
	if (cube->draw_start < 0)
		cube->draw_start = 0;
	cube->draw_end = cube->line_height / 2 + h / 2;
	if (cube->draw_end >= h)
		cube->draw_end = h - 1;
}

int		draw_frame(t_cube *cube)
{
	int	x;

	x = 0;
	mlx_destroy_image(cube->mlx, cube->img.img);
	img_init(cube);
	while (x < cube->largeur)
	{
		init_calcul_cube(cube, x);
		calcul_raydir(cube);
		calcul_distance(cube);
		gestion_dessin(cube);
		calcul_collision_texture(cube);
		verline(x, cube->draw_start, cube->draw_end, cube);
		cube->sprite_buffer[x] = cube->perp_wall_dist;
		x++;
	}
	if (!(init_sprite(cube)))
		return (0);
	mlx_put_image_to_window(cube->mlx, cube->window, cube->img.img, 0, 0);
	if (cube->save)
	{
		save_bmp(cube);
		exit(0);
	}
	return (1);
}
