/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:14:44 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 16:55:45 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		get_color_image(t_cube *cube, int x, int y, int orientation)
{
	char	*dst;

	if (orientation == 1)
		dst = cube->txt.nord.addr + (y * cube->txt.nord.line_length +
				x * (cube->txt.nord.bits_per_pixel / 8));
	else if (orientation == 2)
		dst = cube->txt.sud.addr + (y * cube->txt.sud.line_length +
				x * (cube->txt.sud.bits_per_pixel / 8));
	else if (orientation == 3)
		dst = cube->txt.ouest.addr + (y * cube->txt.ouest.line_length +
				x * (cube->txt.ouest.bits_per_pixel / 8));
	else if (orientation == 4)
		dst = cube->txt.est.addr + (y * cube->txt.est.line_length +
				x * (cube->txt.est.bits_per_pixel / 8));
	else
		dst = cube->txt.sprite.addr + (y * cube->txt.sprite.line_length +
				x * (cube->txt.sprite.bits_per_pixel / 8));
	return (*(int*)dst);
}

int		get_orientation(t_cube *cube)
{
	if (cube->map[cube->map_x][cube->map_y] == '1')
	{
		if (cube->side == 0 && cube->ray_dir_x > 0)
			return (1);
		else if (cube->side == 0 && cube->ray_dir_x < 0)
			return (2);
		else if (cube->side == 1 && cube->ray_dir_y > 0)
			return (3);
		else
			return (4);
	}
	else if (cube->map[cube->map_x][cube->map_y] == '2')
		return (5);
	else
		return (6);
}
