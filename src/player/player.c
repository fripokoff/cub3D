/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:20 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 12:56:04 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initializes the player's state based on the starting position in the map.
** Sets the initial angle based on the direction character (N, S, E, W).
** Converts map grid coordinates to actual pixel coordinates.
** Initializes all movement state flags to false.
** ----------------------------------------------------------------------------
** @param game: The game state containing player and map information
*/

void	init_player(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = game->player.x;
	player_y = game->player.y;
	if (game->map.map[player_y][player_x] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map.map[player_y][player_x] == 'S')
		game->player.angle = PI / 2;
	else if (game->map.map[player_y][player_x] == 'E')
		game->player.angle = 0;
	else if (game->map.map[player_y][player_x] == 'W')
		game->player.angle = PI;
	game->player.x = player_x * WALL_SIZE + WALL_SIZE / 2;
	game->player.y = player_y * WALL_SIZE + WALL_SIZE / 2;
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

/*
** Handles key press events for player movement and game control.
** Updates the player's state flags for movement processing in the next frame.
** Supports:
**  - WASD keys for movement
**  - Left/Right arrow keys for rotation
**  - ESC key to exit the game
** ----------------------------------------------------------------------------
** @param keycode: The key code of the pressed key
** @param player: Pointer to the player structure to update
** @return: Always returns 0 (success)
*/

int	key_press(int keycode, t_player *player)
{
	if (keycode == ESC)
		exit_game(player->game);
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

/*
** Handles key release events for player movement.
** Resets the player's state flags when keys are released.
** ----------------------------------------------------------------------------
** @param keycode: The key code of the released key
** @param player: Pointer to the player structure to update
** @return: Always returns 0 (success)
*/

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

/*
** BONUS
** Collision detection function that checks if a point touches a wall.
** Converts pixel coordinates to map grid coordinates and checks:
**  1. If the point is outside the map boundaries
**  2. If the point is inside a wall cell ('1')
** ----------------------------------------------------------------------------
** @param px: X-coordinate of the point to check
** @param py: Y-coordinate of the point to check
** @param game: Game state containing the map information
** @return: true if collision detected, false otherwise
*/

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = floor(px / WALL_SIZE);
	y = floor(py / WALL_SIZE);
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (true);
	if (game->map.map[y][x] == '1')
		return (true);
	return (false);
}

/*
** Validates the field of view (FOV) setting and initializes
** the game environment.
** FOV must be between 45 and 90 degrees for proper rendering.
** ----------------------------------------------------------------------------
** @param game: Game state to initialize
** @param choosed_texture: The texture set index to use
** @param choosed_size_map: The map size option to use
** @return: 0 on success, 1 on failure
*/

int	check_fov_and_init(t_game *game, int choosed_texture, int choosed_size_map)
{
	if (FOV > 90 || FOV < 45)
	{
		printf("Error\nFOV must be between 45 and 90 degrees.\n");
		return (1);
	}
	if (setup_game_environment(game, choosed_texture, choosed_size_map) == 1)
		return (1);
	return (0);
}
