/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:08 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 11:22:21 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

int	check_fov_and_init(t_game *game)
{
	if (FOV > 90 || FOV < 45)
	{
		printf("Error\nFOV must be between 45 and 90 degrees.\n");
		return (1);
	}
	if (setup_game_environment(game) == 1)
		return (1);
	return (0);
}

int	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
	mlx_loop_hook(game->mlx, render_game_frame, game);
	mlx_hook(game->win, FOCUS_OUT, 1L << 21, focus_out, &game->player);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	if (check_fov_and_init(&game) == 1)
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
