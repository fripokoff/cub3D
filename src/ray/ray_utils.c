/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:22 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 12:51:29 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Calculates corrected distance to prevent fish-eye effect.
** Applies the cosine correction based on the angle,
** between ray and player direction.
** ----------------------------------------------------------------------------
** @param player: Player data (position, direction)
** @param ray: Coordinates of the ray hit
** @return: The corrected distance value
*/

float	fixed_dist(t_player *player, float ray[2])
{
	float	delta_x;
	float	delta_y;
	float	angle_diff;
	float	dist;

	delta_x = ray[0] - player->x;
	delta_y = ray[1] - player->y;
	angle_diff = atan2(delta_y, delta_x) - player->angle;
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

static double	get_time(void)
{
	static double	last_time = 0.0;
	static int		frame_count = 0;
	double			frame_time;

	frame_count++;
	frame_time = 0.016667;
	last_time = frame_count * frame_time;
	return (last_time);
}

double	get_delta_time(void)
{
	static double	last_time = 0.0;
	double			current_time;
	double			delta_time;

	current_time = get_time();
	delta_time = current_time - last_time;
	last_time = current_time;
	if (delta_time > 0.1)
		delta_time = 0.1;
	return (delta_time);
}
