/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:08 by kpires            #+#    #+#             */
/*   Updated: 2025/04/03 00:55:14 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	int		choosed_size_map;
	int		choosed_texture;

	(void)ac;
	(void)av;
	printf("\033[1;36m==========================\033[0m\n");
	printf("\033[1;33mUsage\033[0m \033[1;32m./cub3D [texture] [map_size]\033[0m\n");
	printf("\033[1;35mChoose your texture:\033[0m \033[1;34m0 = cardinal(N,S,W,E), 1 = minecraft\033[0m\n");
	printf("\033[1;35mChoose your map_size:\033[0m \033[1;34m0 = very small, 1 = small, 2 = big\033[0m\n");
	choosed_texture = 0;
	choosed_size_map = 0;
	if (av[1])
		choosed_texture = atoi(av[1]);
	if (av[2])
		choosed_size_map = atoi(av[2]);
	if (check_fov_and_init(&game, choosed_texture, choosed_size_map) == 1)
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
