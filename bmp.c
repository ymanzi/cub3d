/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:03:06 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/08 16:59:24 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int	write_bmp_header(int fd, int filesize, t_cube *cube)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = cube->largeur;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = cube->longueur;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int	get_color(t_cube *cube, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(cube->img.addr + (y * cube->img.line_length
				+ x * (cube->img.bits_per_pixel / 8)));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	write_bmp_data(int file, t_cube *cube)
{
	int					i;
	int					j;
	int					color;

	i = cube->longueur;
	while (i-- > 0)
	{
		j = 0;
		while (j < cube->largeur)
		{
			color = get_color(cube, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			j++;
		}
	}
	return (1);
}

int			save_bmp(t_cube *cube)
{
	int	filesize;
	int	file;

	filesize = 54 + (3 * ((int)cube->longueur) * (int)cube->largeur);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
					| O_TRUNC | O_APPEND)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, cube))
		return (0);
	if (!write_bmp_data(file, cube))
		return (0);
	close(file);
	return (1);
}
