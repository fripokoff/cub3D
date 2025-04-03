/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:20 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 15:51:41 by fripok           ###   ########.fr       */
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
	game->player.moves[MOVE_UP] = 0;
	game->player.moves[MOVE_DOWN] = 0;
	game->player.moves[MOVE_LEFT] = 0;
	game->player.moves[MOVE_RIGHT] = 0;
	game->player.moves[ROTATE_LEFT] = 0;
	game->player.moves[ROTATE_RIGHT] = 0;
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
		player->moves[MOVE_UP] = 1;
	if (keycode == S)
		player->moves[MOVE_DOWN] = 1;
	if (keycode == A)
		player->moves[MOVE_LEFT] = 1;
	if (keycode == D)
		player->moves[MOVE_RIGHT] = 1;
	if (keycode == LEFT)
		player->moves[ROTATE_LEFT] = 1;
	if (keycode == RIGHT)
		player->moves[ROTATE_RIGHT] = 1;
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
		player->moves[MOVE_UP] = 0;
	if (keycode == S)
		player->moves[MOVE_DOWN] = 0;
	if (keycode == A)
		player->moves[MOVE_LEFT] = 0;
	if (keycode == D)
		player->moves[MOVE_RIGHT] = 0;
	if (keycode == LEFT)
		player->moves[ROTATE_LEFT] = 0;
	if (keycode == RIGHT)
		player->moves[ROTATE_RIGHT] = 0;
	return (0);
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
