/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:22 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 16:00:23 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
