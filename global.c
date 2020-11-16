/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:18:46 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 13:46:39 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	ver_init(t_parsing *parse, t_cube *cube)
{
	img_init(cube);
	if (!texture_init(cube, parse))
		return (0);
	return (1);
}

static int	ft_close(t_cube *cube)
{
	int i;

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
	exit(0);
	return (1);
}

static int	ft_boucle(t_cube *cube)
{
	while (!cube->done)
	{
		if (!draw_frame(cube))
			return (0);
		mlx_hook(cube->window, 2, 1L << 0, key_hook, cube);
		mlx_hook(cube->window, 17, 0, ft_close, cube);
		mlx_loop(cube->mlx);
	}
	return (1);
}

int			global(int save, char *map)
{
	t_parsing	parse;
	t_cube		cube;
	int			fd;

	fd = open(map, O_RDONLY);
	ft_bzero(&cube, sizeof(cube));
	if (fd == -1)
		return (ft_error("fd error"));
	if (!(get_parsing(&parse, fd)) ||
			!(cube_init(&cube, &parse, save)))
		return (0);
	if (!(cube.map = ft_split(parse.map, ' ')) || !ver_init(&parse, &cube))
	{
		free_cube(&parse);
		free_cube_c(&cube, 1);
		return (0);
	}
	free_cube(&parse);
	if (!ft_boucle(&cube))
		return (0);
	return (free_cube_c(&cube, 1));
}
