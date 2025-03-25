/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:43:53 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:56:47 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1280
# define HEIGHT 720
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define BLUE_HEX 0x0000FF
# define GREEN_HEX 0x00FF00
# define WALL_SIZE 64
# define PLAYER_SPEED 5
# define PLAYER_ROT_SPEED 0.05
# define FOV 60
# define FOCUS_OUT 10
# define PI 3.14159265359

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>

typedef struct s_player
{
	float			x;
	float			y;
	float			pos_x;
	float			pos_y;
	float			angle;
	struct s_game	*game;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_player	player;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	t_texture	textures[4];
}	t_game;

typedef struct s_wall_column
{
	int		column_id;// position x dans l'écran
	float	wall_x;// position x sur la texture
	int		tex_id;// identifiant de la texture
	float	wall_height;// hauteur du mur
	int		draw_start;// début du rendu vertical
	int		draw_end;// fin du rendu vertical
}	t_wall_column;

/* INIT */
int		setup_game_environment(t_game *game, int debug_choosed_map);

/* PLAYER & MOVEMENTS */
void	init_player(t_game *player);
int		check_fov_and_init(t_game *game, int debug_choosed_map);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_player *player);
bool	touch(float px, float py, t_game *game);
void	move_player(t_player *player);
int		focus_out(t_player *player);

/* RENDER */
int		load_texture(t_game *game, t_texture *text, char *path);
void	put_pixel(int x, int y, int color, t_game *game);
int		get_texture_pixel(t_texture *text, int x, int y);
int		render_game_frame(t_game *game);

/* RAY */
float	get_precise_wall_hit(float ray[2], float old_ray[2], t_game *game);
float	lerp(float a, float b, float t);
float	fixed_dist(t_player *player, float ray[2], t_game *game);
void	render_wall_column(t_player *player, t_game *game,
			float start_x, int i);

/* UTILS & MLX UTILS */
void	clear_image(t_game *game);
int		rgb_to_int(int r, int g, int b);

#endif