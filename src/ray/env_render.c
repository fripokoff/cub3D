/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:21:13 by kpires            #+#    #+#             */
/*   Updated: 2025/04/04 14:30:12 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

/*
** This function renders the floor of the environment.
** It fills the bottom half of the screen with the floor color.
** ----------------------------------------------------------------------------
** @param game: The game state containing all rendering information
*/

static void	render_floor(t_game *game)
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

/*
** This function renders the ceiling of the environment.
** It fills the top half of the screen with the ceiling color.
** ----------------------------------------------------------------------------
** @param game: The game state containing all rendering information
*/

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

/*
** The main rendering function called each frame.
** Responsible for:
**  1. Updating player position
**  2. Clearing the screen
**  3. Rendering the ceiling and floor
**  4. Casting rays for each vertical column of the screen
**  5. Displaying the rendered image
** ----------------------------------------------------------------------------
** @param game: The game state containing all rendering information
** @return: Always returns 0 (success)
*/

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
