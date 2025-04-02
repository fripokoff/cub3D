/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:08 by kpires            #+#    #+#             */
/*   Updated: 2025/04/02 16:03:01 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	int		choosed_map;

	(void)ac;
	(void)av;
	choosed_map = 0;
	if (av[1])
		choosed_map = atoi(av[1]);
	if (check_fov_and_init(&game, choosed_map) == 1)
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
