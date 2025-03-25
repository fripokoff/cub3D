/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:27:26 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 12:30:00 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**initialize_game_map(t_player *player)
{
	char	**map;
	int		map_size;
	int		player_count;
	int		i;
	int		j;

	map_size = 11;
	map = malloc(sizeof(char *) * map_size);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000000000001";
	map[6] = "100011101110001";
	map[7] = "1000100S0011011";
	map[8] = "100010000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	player_count = 0;
	i = 0;
	j = 0;
	while (i < map_size - 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->x = j * WALL_SIZE + WALL_SIZE / 2;
				player->y = i * WALL_SIZE + WALL_SIZE / 2;
				player->pos_x = j;
				player->pos_y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Error\nThere must be exactly one player \
start position (N, S, E, W).\n");
		return (NULL);
	}
	return (map);
}

static int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error: mlx initialization failed\n"), 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cubi");
	if (!game->win)
		return (printf("Error: window creation failed\n"), 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Error: image creation failed\n"), 1);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
		return (printf("Error: getting image data failed\n"), 1);
	return (0);
}

static int	load_cardinal_textures(t_game *game)
{
	if (load_texture(game, &game->textures[0], "textures/cardinal/NO.xpm")
		|| load_texture(game, &game->textures[1], "textures/cardinal/SO.xpm")
		|| load_texture(game, &game->textures[2], "textures/cardinal/EA.xpm")
		|| load_texture(game, &game->textures[3], "textures/cardinal/WE.xpm"))
	{
		printf("Error: loading cardinal textures failed\n");
		return (1);
	}
	return (0);
}

static int	load_wolf_textures(t_game *game)
{
	if (load_texture(game, &game->textures[0], "textures/wolf/wood.xpm")
		|| load_texture(game, &game->textures[1], "textures/wolf/red_brick.xpm")
		|| load_texture(game, &game->textures[2],
			"textures/wolf/grey_stone.xpm")
		|| load_texture(game, &game->textures[3],
			"textures/wolf/purple_stone.xpm"))
	{
		printf("Error: loading wolf textures failed\n");
		return (1);
	}
	return (0);
}

int	setup_game_environment(t_game *game, int debug_choosed_map)
{
	if (init_mlx_components(game))
		return (1);
	game->map = initialize_game_map(&game->player);
	if (!game->map)
		return (printf("Error: map initialization failed\n"), 1);
	init_player(game);
	if (debug_choosed_map)
	{
		if (load_wolf_textures(game))
			return (1);
	}
	else
	{
		if (load_cardinal_textures(game))
			return (1);
	}
	game->player.game = game;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized successfully\n");
	return (0);
}
