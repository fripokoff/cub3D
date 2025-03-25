/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:13 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:19:51 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	player_rotate(t_player *player)
{
	if (player->left_rotate)
		player->angle = fmod(player->angle - PLAYER_ROT_SPEED + 2 * PI, 2 * PI);
	if (player->right_rotate)
		player->angle = fmod(player->angle + PLAYER_ROT_SPEED, 2 * PI);
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
}

static void	player_movements(t_player *player, float *dx, float *dy)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*dx += cos_angle * PLAYER_SPEED;
		*dy += sin_angle * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		*dx -= cos_angle * PLAYER_SPEED;
		*dy -= sin_angle * PLAYER_SPEED;
	}
	if (player->key_left)
	{
		*dx += sin_angle * PLAYER_SPEED;
		*dy -= cos_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		*dx -= sin_angle * PLAYER_SPEED;
		*dy += cos_angle * PLAYER_SPEED;
	}
}

static void	player_colision(t_player *player, float dx, float dy)
{
	bool	can_move_x;
	bool	can_move_y;
	float	margin;

	margin = 10.0f;
	can_move_x = !touch(dx + margin, player->y + margin, player->game)
		&& !touch(dx - margin, player->y - margin, player->game)
		&& !touch(dx + margin, player->y - margin, player->game)
		&& !touch(dx - margin, player->y + margin, player->game);
	can_move_y = !touch(player->x + margin, dy + margin, player->game)
		&& !touch(player->x - margin, dy - margin, player->game)
		&& !touch(player->x + margin, dy - margin, player->game)
		&& !touch(player->x - margin, dy + margin, player->game);
	if (can_move_x)
		player->x = dx;
	if (can_move_y)
		player->y = dy;
}

void	move_player(t_player *player)
{
	float	dx;
	float	dy;

	dx = 0;
	dy = 0;
	player_rotate(player);
	player_movements(player, &dx, &dy);
	player_colision(player, player->x + dx, player->y + dy);
}

int	focus_out(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	return (0);
}
