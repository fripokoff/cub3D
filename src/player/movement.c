/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:13 by kpires            #+#    #+#             */
/*   Updated: 2025/04/02 19:24:55 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	player_rotate(t_player *player)
{
	double	player_rot_speed;
	double	rot_speed;
	double	delta_time;

	delta_time = get_delta_time();
	player_rot_speed = (double)PLAYER_ROT_SPEED / 3;
	rot_speed = player_rot_speed * delta_time;
	if (player->left_rotate)
		player->angle -= rot_speed;
	if (player->right_rotate)
		player->angle += rot_speed;
	while (player->angle < 0)
		player->angle += 2 * PI;
	while (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

static void	player_movements(t_player *player, double *dx, double *dy,
		double delta_time)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*dx += cos_angle * player->speed * delta_time * 20 * 1.5;
		*dy += sin_angle * player->speed * delta_time * 20 * 1.5;
	}
	if (player->key_down)
	{
		*dx -= cos_angle * player->speed * delta_time * 20 * 1.5;
		*dy -= sin_angle * player->speed * delta_time * 20 * 1.5;
	}
	if (player->key_left)
	{
		*dx += sin_angle * player->speed * delta_time * 20;
		*dy -= cos_angle * player->speed * delta_time * 20;
	}
	if (player->key_right)
	{
		*dx -= sin_angle * player->speed * delta_time * 20;
		*dy += cos_angle * player->speed * delta_time * 20;
	}
}

static void	player_colision(t_player *player, double dx, double dy)
{
	bool	can_move_x;
	bool	can_move_y;
	double	margin;

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
	double	dx;
	double	dy;
	double	delta_time;

	dx = 0;
	dy = 0;
	delta_time = get_delta_time();
	player_rotate(player);
	player_movements(player, &dx, &dy, delta_time);
	player_colision(player, player->x + dx, player->y + dy);
}
