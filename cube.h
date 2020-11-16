/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:20:41 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 13:36:10 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUBE_H
#	define CUBE_H

#include <stdlib.h>
#include "mlx/mlx.h"
#include "parse/cube_parsing.h"
#include <math.h>
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_DOWN 125
#define KEY_UP 126
#define TEXTURE_H 64
#define TEXWIDTH 64
#define TEXHEIGHT 64
#define TEXTURE_L 64

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	distance;
}				t_sprite;

typedef struct	s_texture
{
	t_img	nord;
	t_img	sud;
	t_img	est;
	t_img	ouest;
	t_img	sprite;
}				t_texture;

typedef struct	s_cube
{
	void		*mlx;
	void		*window;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			longueur;
	int			largeur;
	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			done;
	int			color_floor;
	int			color_ceiling;
	int			color;
	char		**map;
	t_img		img;
	t_texture	txt;
	int			nbr_sprite;
	t_sprite	*lst_sprite;
	double		*sprite_buffer;
	double		sprite_x;
	double		sprite_y;
	double		inv_cam_matrix;
	double		trans_x;
	double		trans_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			save;
}				t_cube;

/*
** Sprite.c
*/
int				init_sprite(t_cube *cube);
int				free_cube_c(t_cube *cube, int ret);
/*
** sprite2.c
*/
int				get_nbr_sprite(t_cube *cube);
int				get_coord_sprite(t_cube *cube);
void			sprite_distance(t_cube *cube);
void			sprite_swipt(t_sprite *one, t_sprite *two);
void			sort_sprite(t_cube *cube);
/*
** set_dir.c
*/
void			set_dir(t_cube *cube, t_parsing *parse);
/*
** init.c
*/
int				img_init(t_cube *cube);
int				cube_init(t_cube *cube, t_parsing *parse, int save);
int				texture_init(t_cube *cube, t_parsing *parse);
int				set_rgb(int r, int g, int b);
/*
** keys_fct.c
*/
void			key_w_s(int keycode, t_cube *cube);
void			key_a_d(int keycode, t_cube *cube);
void			key_left_right(int keycode, t_cube *cube);
int				key_hook(int keycode, t_cube *cube);
/*
** algo.c
*/
void			init_calcul_cube(t_cube *cube, int x);
void			calcul_raydir(t_cube *cube);
void			calcul_distance(t_cube *cube);
void			calcul_collision_texture(t_cube *cube);
/*
** dessin.c
*/
void			my_mlx_pixel_put(t_cube *cube, int x, int y, int color);
void			verline(int x, int draw_start, int draw_end, t_cube *cube);
void			gestion_dessin(t_cube *cube);
int				draw_frame(t_cube *cube);
/*
** algo_orientation.c
*/
int				get_color_image(t_cube *cube, int x, int y, int orientation);
int				get_orientation(t_cube *cube);
/*
** global.c
*/
int				global(int save, char *map);
/*
** bmp.c
*/
int				save_bmp(t_cube *cube);

#	endif
