/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:21:13 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 01:03:12 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void render_floor(t_game *game)
{
	int		y;
	int		x;
	int		floor_color;

	y = HEIGHT / 2;
	floor_color = rgb_to_int(game->map.floor_color[0],
			game->map.floor_color[1], game->map.floor_color[2]);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, floor_color, game);
			x++;
		}
		y++;
	}
}

static void	render_ceiling(t_game *game)
{
	int		y;
	int		x;
	int		ceiling_color;
	
	ceiling_color = rgb_to_int(game->map.ceiling_color[0],
			game->map.ceiling_color[1], game->map.ceiling_color[2]);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, ceiling_color, game);
			x++;
		}
		y++;
	}
}

int	render_game_frame(t_game *game)
{
	int			screen_x;
	float		camera_x;
	float		ray_angle;
	t_player	*player;
	float		fov;

	player = &game->player;
	move_player(player);
	clear_image(game);
	render_ceiling(game);
	render_floor(game);
	screen_x = 0;
	fov = FOV * PI / 180.0;
	while (screen_x < WIDTH)
	{
		camera_x = 2 * screen_x / (float)WIDTH - 1;
		ray_angle = player->angle + atan(camera_x * tan(fov / 2));
		render_wall_column(player, game, ray_angle, screen_x);
		screen_x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	load_texture(t_game *game, t_texture *text, char *path)
{
	text->img = mlx_xpm_file_to_image(game->mlx, path,
			&text->width, &text->height);
	if (!text->img)
		return (1);
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
	return (0);
}

int	get_texture_pixel(t_texture *text, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= text->width || y < 0 || y >= text->height)
		return (0);
	pixel = text->addr + (y * text->line_length
			+ x * (text->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}
