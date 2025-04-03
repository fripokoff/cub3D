/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:13 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 15:52:03 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Handles player rotation based on keyboard input.
** Updates the player's viewing angle when rotation keys are pressed.
** Normalizes the angle to stay within [0, 2π] range.
** ----------------------------------------------------------------------------
** @param player: The player structure to update
** @param delta_time: Time elapsed since last frame for smooth rotation
*/

static void	player_rotate(t_player *player)
{
	double	player_rot_speed;
	double	rot_speed;
	double	delta_time;

	delta_time = get_delta_time();
	player_rot_speed = (double)PLAYER_ROT_SPEED / 3;
	rot_speed = player_rot_speed * delta_time;
	if (player->moves[ROTATE_LEFT])
		player->angle -= rot_speed;
	if (player->moves[ROTATE_RIGHT])
		player->angle += rot_speed;
	while (player->angle < 0)
		player->angle += 2 * PI;
	while (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

/*
** Calculates the player's new position based on current input state.
** Handles WASD keys for forward/backward and strafing movements.
** Adjusts movement speed based on elapsed time for consistent motion.
** ----------------------------------------------------------------------------
** @param player: The player structure to update
** @param delta_time: Time elapsed since last frame for smooth movement
*/

static void	player_movements(t_player *player, double *dx, double *dy,
		double delta_time)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->moves[MOVE_UP])
	{
		*dx += cos_angle * PLAYER_SPEED * delta_time * 20 * 1.5;
		*dy += sin_angle * PLAYER_SPEED * delta_time * 20 * 1.5;
	}
	if (player->moves[MOVE_DOWN])
	{
		*dx -= cos_angle * PLAYER_SPEED * delta_time * 20 * 1.5;
		*dy -= sin_angle * PLAYER_SPEED * delta_time * 20 * 1.5;
	}
	if (player->moves[MOVE_LEFT])
	{
		*dx += sin_angle * PLAYER_SPEED * delta_time * 20;
		*dy -= cos_angle * PLAYER_SPEED * delta_time * 20;
	}
	if (player->moves[MOVE_RIGHT])
	{
		*dx -= sin_angle * PLAYER_SPEED * delta_time * 20;
		*dy += cos_angle * PLAYER_SPEED * delta_time * 20;
	}
}

/*
** Main function for updating player position based on key inputs.
** Processes rotation and movement requests from keyboard state.
** ----------------------------------------------------------------------------
** @param player: The player structure containing position and input state
*/

void	move_player(t_player *player)
{
	double	dx;
	double	dy;
	double	delta_time;

	dx = 0;
	dy = 0;
	delta_time = get_delta_time();
	player_rotate(player);
	player_movements(player, &dx, &dy, delta_time);
	player->x += dx;
	player->y += dy;
}
