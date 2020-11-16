/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:04:11 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 13:41:10 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int			img_init(t_cube *cube)
{
	cube->img.img = mlx_new_image(cube->mlx, cube->largeur, cube->longueur);
	cube->img.addr = mlx_get_data_addr(cube->img.img,
&cube->img.bits_per_pixel, &cube->img.line_length, &cube->img.endian);
	return (1);
}

int			cube_init(t_cube *cube, t_parsing *parse, int save)
{
	cube->pos_x = (double)parse->py;
	cube->pos_y = (double)parse->px;
	set_dir(cube, parse);
	cube->save = save;
	cube->largeur = parse->x;
	if (!(cube->sprite_buffer = (double*)malloc(sizeof(double) * parse->x)))
	{
		free_cube(parse);
		return (free_cube_c(cube, 0));
	}
	cube->longueur = parse->y;
	cube->mlx = mlx_init();
	cube->window = mlx_new_window(cube->mlx,
		cube->largeur, cube->longueur, "Raycaster");
	cube->color_ceiling = set_rgb(parse->plafond_r,
			parse->plafond_g, parse->plafond_b);
	cube->color_floor = set_rgb(parse->sol_r,
			parse->sol_g, parse->sol_b);
	cube->done = 0;
	return (1);
}

static void	texture_init2(t_cube *cube)
{
	cube->txt.nord.addr = mlx_get_data_addr(cube->txt.nord.img, &cube->txt
.nord.bits_per_pixel, &cube->txt.nord.line_length, &cube->txt.nord.endian);
	cube->txt.sud.addr = mlx_get_data_addr(cube->txt.sud.img, &cube->txt
.sud.bits_per_pixel, &cube->txt.sud.line_length, &cube->txt.sud.endian);
	cube->txt.est.addr = mlx_get_data_addr(cube->txt.est.img, &cube->txt
.est.bits_per_pixel, &cube->txt.est.line_length, &cube->txt.est.endian);
	cube->txt.ouest.addr = mlx_get_data_addr(cube->txt.ouest.img, &cube->txt
.ouest.bits_per_pixel, &cube->txt.ouest.line_length, &cube->txt.ouest.endian);
	cube->txt.sprite.addr = mlx_get_data_addr(cube->txt.sprite.img,
	&cube->txt.sprite.bits_per_pixel,
	&cube->txt.sprite.line_length, &cube->txt.sprite.endian);
}

int			texture_init(t_cube *cube, t_parsing *parse)
{
	int	texture_l;

	texture_l = 64;
	cube->txt.nord.img = mlx_xpm_file_to_image(cube->mlx,
			parse->north, &texture_l, &texture_l);
	cube->txt.sud.img = mlx_xpm_file_to_image(cube->mlx,
			parse->south, &texture_l, &texture_l);
	cube->txt.est.img = mlx_xpm_file_to_image(cube->mlx,
			parse->east, &texture_l, &texture_l);
	cube->txt.ouest.img = mlx_xpm_file_to_image(cube->mlx,
			parse->west, &texture_l, &texture_l);
	cube->txt.sprite.img = mlx_xpm_file_to_image(cube->mlx,
			parse->sprite, &texture_l, &texture_l);
	if (!cube->txt.nord.img || !cube->txt.sud.img || !cube->txt.est.img
			|| !cube->txt.ouest.img || !cube->txt.sprite.img)
		return (ft_error("L'une des textures n'existe pas"));
	texture_init2(cube);
	return (1);
}

int			set_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
