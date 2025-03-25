/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:27:26 by kpires            #+#    #+#             */
/*   Updated: 2025/03/25 10:21:30 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	setup_game_environment(t_game *game)
{
	// Initialiser MLX en premier
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: mlx initialization failed\n");
		return (1);
	}
	// Initialiser la map et le joueur
	game->map = initialize_game_map(&game->player);
	if (!game->map)
	{
		printf("Error: map initialization failed\n");
		return (1);
	}
	init_player(game);
	// Charger les textures
	if (load_texture(game, &game->textures[0], "textures/cardinal/NO.xpm")
		|| load_texture(game, &game->textures[1], "textures/cardinal/SO.xpm")
		|| load_texture(game, &game->textures[2], "textures/cardinal/EA.xpm")
		|| load_texture(game, &game->textures[3], "textures/cardinal/WE.xpm"))
	// if (load_texture(game, &game->textures[0], "textures/wolf/wood.xpm")
	// 	|| load_texture(game, &game->textures[1], "textures/wolf/red_brick.xpm")
	// 	|| load_texture(game, &game->textures[2], "textures/wolf/grey_stone.xpm")
	// 	|| load_texture(game, &game->textures[3], "textures/wolf/purple_stone.xpm"))
	{
		printf("Error: loading textures failed\n");
		return (1);
	}
	// Créer la fenêtre
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cubi");
	if (!game->win)
	{
		printf("Error: window creation failed\n");
		return (1);
	}
	// Créer l'image
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		printf("Error: image creation failed\n");
		return (1);
	}
	// Obtenir l'adresse des données de l'image
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!game->data)
	{
		printf("Error: getting image data failed\n");
		return (1);
	}
	game->player.game = game;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized successfully\n");
	return (0);
}
