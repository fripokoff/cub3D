/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:20 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:29:58 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = game->player.pos_x;
	player_y = game->player.pos_y;
	if (game->map[player_y][player_x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map[player_y][player_x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map[player_y][player_x] == 'E')
		game->player.angle = 0;
	else if (game->map[player_y][player_x] == 'W')
		game->player.angle = PI;
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / WALL_SIZE;
	y = py / WALL_SIZE;
	if (x < 0 || y < 0 || x >= (int)strlen(game->map[0]) || y >= 10)
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int	check_fov_and_init(t_game *game, int debug_choosed_map)
{
	if (FOV > 90 || FOV < 45)
	{
		printf("Error\nFOV must be between 45 and 90 degrees.\n");
		return (1);
	}
	if (setup_game_environment(game, debug_choosed_map) == 1)
		return (1);
	return (0);
}
