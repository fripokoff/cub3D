/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:35 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:51:45 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	cast_ray_to_wall(t_player *player, t_game *game, float *angles,
	float *ray_coords)
{
	float	ray[2];
	float	old_ray[2];
	float	ray_step;
	double	hit_point;

	ray[0] = player->x;
	ray[1] = player->y;
	ray_step = 0.3;
	while (!touch(ray[0], ray[1], game))
	{
		old_ray[0] = ray[0];
		old_ray[1] = ray[1];
		ray[0] += angles[0] * ray_step;
		ray[1] += angles[1] * ray_step;
	}
	hit_point = get_precise_wall_hit(ray, old_ray, game);
	ray_coords[0] = lerp(old_ray[0], ray[0], hit_point);
	ray_coords[1] = lerp(old_ray[1], ray[1], hit_point);
}

static void	select_wall_texture(float ray_coords[2], float angles[2],
	bool hit_vertical, t_wall_column *wall)
{
	if (hit_vertical)
	{
		wall->wall_x = fmod(ray_coords[1], WALL_SIZE) / WALL_SIZE;
		wall->tex_id = 3;
		if (angles[0] > 0)
			wall->tex_id = 2;
		else
			wall->wall_x = 1.0 - wall->wall_x;
	}
	else
	{
		wall->wall_x = fmod(ray_coords[0], WALL_SIZE) / WALL_SIZE;
		if (angles[1] > 0)
		{
			wall->tex_id = 1;
			wall->wall_x = 1.0 - wall->wall_x;
		}
		else
			wall->tex_id = 0;
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

	step = 1.0 * game->textures[wall->tex_id].height / wall->wall_height;
	tex_pos = (wall->draw_start - HEIGHT / 2 + wall->wall_height / 2) * step;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)tex_pos & (game->textures[wall->tex_id].height - 1);
		tex_pos += step;
		color = get_texture_pixel(&game->textures[wall->tex_id],
				(int)(wall->wall_x * game->textures[wall->tex_id].width),
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
	dist = fixed_dist(player, ray_coords, game);
	hit_vertical = fabs(ray_coords[0] - round(ray_coords[0] / WALL_SIZE)
			* WALL_SIZE) < 0.001;
	wall.column_id = i;
	select_wall_texture(ray_coords, angles,
		hit_vertical, &wall);
	compute_wall_dimensions(dist, &wall.draw_start, &wall.draw_end,
		&wall.wall_height);
	render_textured_wall_column(game, &wall);
}
