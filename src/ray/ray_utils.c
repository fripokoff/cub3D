/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:22 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:25:52 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	fixed_dist(t_player *player, float ray[2], t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle_diff;
	float	dist;

	delta_x = ray[0] - player->x;
	delta_y = ray[1] - player->y;
	angle_diff = atan2(delta_y, delta_x) - game->player.angle;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle_diff);
	return (dist);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

float	get_precise_wall_hit(float ray[2], float old_ray[2], t_game *game)
{
	float	precision;
	float	t;
	float	step;
	float	test_x;
	float	test_y;

	precision = 0.00001;
	t = 0.0;
	step = 0.5;
	while (step > precision)
	{
		test_x = lerp(old_ray[0], ray[0], t);
		test_y = lerp(old_ray[1], ray[1], t);
		if (touch(test_x, test_y, game))
			t -= step;
		else
			t += step;
		step *= 0.5;
	}
	return (t);
}
