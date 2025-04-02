/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:50:29 by fripok            #+#    #+#             */
/*   Updated: 2025/04/02 19:44:13 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray_data(t_player *player, float *angles, t_ray_data *data)
{
	int	map_x;
	int	map_y;

	data->ray_dir[0] = angles[0];
	data->ray_dir[1] = angles[1];
	map_x = (int)(player->x / WALL_SIZE);
	map_y = (int)(player->y / WALL_SIZE);
	data->map[0] = map_x;
	data->map[1] = map_y;
	if (fabs(data->ray_dir[0]) < 1e-10)
		data->delta_dist[0] = 1e6;
	else
		data->delta_dist[0] = fabs(1.0 / data->ray_dir[0]);
	if (fabs(data->ray_dir[1]) < 1e-10)
		data->delta_dist[1] = 1e6;
	else
		data->delta_dist[1] = fabs(1.0 / data->ray_dir[1]);
}

static void	setup_dda_steps(t_player *player, t_ray_data *data)
{
	if (data->ray_dir[0] < 0)
	{
		data->step[0] = -1;
		data->side_dist[0] = (player->x / WALL_SIZE - data->map[0])
			* data->delta_dist[0];
	}
	else
	{
		data->step[0] = 1;
		data->side_dist[0] = (data->map[0] + 1.0 - player->x / WALL_SIZE)
			* data->delta_dist[0];
	}
	if (data->ray_dir[1] < 0)
	{
		data->step[1] = -1;
		data->side_dist[1] = (player->y / WALL_SIZE - data->map[1])
			* data->delta_dist[1];
	}
	else
	{
		data->step[1] = 1;
		data->side_dist[1] = (data->map[1] + 1.0 - player->y / WALL_SIZE)
			* data->delta_dist[1];
	}
}

static int	perform_dda(t_game *game, t_ray_data *data)
{
	bool	hit;
	int		side;

	hit = false;
	side = 0;
	while (!hit)
	{
		if (data->side_dist[0] < data->side_dist[1])
		{
			data->side_dist[0] += data->delta_dist[0];
			data->map[0] += data->step[0];
			side = 0;
		}
		else
		{
			data->side_dist[1] += data->delta_dist[1];
			data->map[1] += data->step[1];
			side = 1;
		}
		if (data->map[0] < 0 || data->map[1] < 0 || data->map[0]
			>= game->map_width || data->map[1] >= game->map_height
			|| game->map[data->map[1]][data->map[0]] == '1')
			hit = true;
	}
	return (side);
}

static void	calculate_wall_hit(t_player *player, t_ray_data *data,
	float *ray_coords, int side)
{
	if (side == 0)
	{
		ray_coords[0] = data->map[0] * WALL_SIZE;
		ray_coords[1] = player->y;
		if (data->step[0] < 0)
			ray_coords[0] += WALL_SIZE;
		if (fabs(data->ray_dir[0]) > 1e-10)
			ray_coords[1] = player->y + data->ray_dir[1]
				* (ray_coords[0] - player->x) / data->ray_dir[0];
	}
	else
	{
		ray_coords[1] = data->map[1] * WALL_SIZE;
		ray_coords[0] = player->x;
		if (data->step[1] < 0)
			ray_coords[1] += WALL_SIZE;
		if (fabs(data->ray_dir[1]) > 1e-10)
			ray_coords[0] = player->x + data->ray_dir[0]
				* (ray_coords[1] - player->y) / data->ray_dir[1];
	}
}

int	cast_ray_to_wall(t_player *player, t_game *game, float *angles,
	float *ray_coords)
{
	t_ray_data	data;
	int			side;

	init_ray_data(player, angles, &data);
	setup_dda_steps(player, &data);
	side = perform_dda(game, &data);
	calculate_wall_hit(player, &data, ray_coords, side);
	return (side);
}
