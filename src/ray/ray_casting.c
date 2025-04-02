/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:35 by kpires            #+#    #+#             */
/*   Updated: 2025/04/02 23:57:57 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	select_wall_texture(float ray_coords[2], float angles[2],
	bool hit_vertical, t_wall_column *wall)
{
	if (hit_vertical)
	{
		wall->wall_x = fmod(ray_coords[1], WALL_SIZE) / WALL_SIZE;
		wall->tex_id = TEX_WEST;
		if (angles[0] > 0)
			wall->tex_id = TEX_EAST;
		else
			wall->wall_x = 1.0 - wall->wall_x;
	}
	else
	{
		wall->wall_x = fmod(ray_coords[0], WALL_SIZE) / WALL_SIZE;
		if (angles[1] > 0)
		{
			wall->tex_id = TEX_SOUTH;
			wall->wall_x = 1.0 - wall->wall_x;
		}
		else
			wall->tex_id = TEX_NORTH;
	}
}

static void	compute_wall_dimensions(float dist, int *draw_start, int *draw_end,
	float *wall_height)
{
	*wall_height = (WALL_SIZE * HEIGHT) / dist;
	*draw_start = -*wall_height / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *wall_height / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

static void	render_textured_wall_column(t_game *game, t_wall_column *wall)
{
	float	step;
	float	tex_pos;
	int		tex_y;
	int		y;
	int		color;

	step = 1.0 * game->map.textures[wall->tex_id].height / wall->wall_height;
	tex_pos = (wall->draw_start - HEIGHT / 2 + wall->wall_height / 2) * step;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)tex_pos & (game->map.textures[wall->tex_id].height - 1);
		tex_pos += step;
		color = get_texture_pixel(&game->map.textures[wall->tex_id],
				(int)(wall->wall_x * game->map.textures[wall->tex_id].width),
				tex_y);
		put_pixel(wall->column_id, y, color, game);
		y++;
	}
}

void	render_wall_column(t_player *player, t_game *game, float start_x, int i)
{
	float			angles[2];
	float			ray_coords[2];
	float			dist;
	t_wall_column	wall;
	bool			hit_vertical;

	angles[0] = cos(start_x);
	angles[1] = sin(start_x);
	cast_ray_to_wall(player, game, angles, ray_coords);
	dist = fixed_dist(player, ray_coords);
	hit_vertical = fabs(fmod(ray_coords[0], WALL_SIZE)) < 0.0001f
		|| fabs(fmod(ray_coords[0], WALL_SIZE) - WALL_SIZE) < 0.0001f;
	wall.column_id = i;
	select_wall_texture(ray_coords, angles,
		hit_vertical, &wall);
	compute_wall_dimensions(dist, &wall.draw_start, &wall.draw_end,
		&wall.wall_height);
	render_textured_wall_column(game, &wall);
}
