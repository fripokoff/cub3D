/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:43:53 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 01:03:32 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.14159265359

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>

typedef enum e_game_settings
{
	WIDTH = 1280,
	HEIGHT = 720,
	WALL_SIZE = 64,
	PLAYER_SPEED = 5,
	PLAYER_ROT_SPEED = 4,
	FOV = 60,
	FOCUS_OUT = 10
}	t_game_settings;

typedef enum e_texture_id
{
	TEX_NORTH = 0,
	TEX_SOUTH = 1,
	TEX_EAST = 2,
	TEX_WEST = 3,
	TEX_COUNT = 4
}	t_texture_id;

typedef enum e_keyboard
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	LEFT = 65361,
	RIGHT = 65363,
	ESC = 65307
}	t_keyboard;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	struct s_game	*game;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
}	t_player;

typedef struct s_ray_data
{
	float	ray_dir[2];
	float	delta_dist[2];
	float	side_dist[2];
	int		map[2];
	int		step[2];
}	t_ray_data;

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

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
	int			floor_color[3];
	int			ceiling_color[3];
	t_texture	textures[TEX_COUNT];
}	t_map;

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
	t_map		map;
}	t_game;

typedef struct s_wall_column
{
	int		screen_x;
	double	wall_x;
	int		tex_id;
	float	wall_height;
	int		draw_start;
	int		draw_end;
}	t_wall_column;

/* INIT */
int		setup_game_environment(t_game *game, int choosed_texture, int choosed_size_map);

/* PLAYER & MOVEMENTS */
void	init_player(t_game *player);
int		check_fov_and_init(t_game *game, int choosed_texture, int choosed_size_map);
int		key_release(int keycode, t_player *player);
int		key_press(int keycode, t_player *player);
bool	touch(float px, float py, t_game *game);
void	move_player(t_player *player);
int		focus_out(t_player *player);

/* RENDER */
int		load_texture(t_game *game, t_texture *text, char *path);
int		get_texture_pixel(t_texture *text, int x, int y);
int		render_game_frame(t_game *game);

/* RAY */
double	get_delta_time(void);
float	fixed_dist(t_player *player, float ray[2]);
void	render_wall_column(t_player *player, t_game *game,
			float start_x, int i);
int		cast_ray_to_wall(t_player *player, t_game *game, float *angles,
			float *ray_coords);

/* UTILS & MLX UTILS */
int		setup_hooks(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
int		rgb_to_int(int r, int g, int b);
int		exit_game(t_game *game);
void	free_map(char **map);

#endif