/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fripok <fripok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:27:26 by kpires            #+#    #+#             */
/*   Updated: 2025/04/04 15:33:13 by fripok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**generate_map(int width, int height)
{
	char	**map;
	int		i;
	int		j;
	int		player_placed;

	player_placed = 0;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i <= height)
	{
		map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (width + 1));
		if (!map[i])
		{
			j = 0;
			while (j < i)
			{
				free(map[j]);
				j++;
			}
			free(map);
			return (NULL);
		}
		j = 0;
		while (j < width)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				map[i][j] = '1';
			else if (!player_placed && i == height / 2 && j == width / 2)
			{
				map[i][j] = 'N';
				player_placed = 1;
			}
			else if (rand() % 10 == 0)
				map[i][j] = '1';
			else
				map[i][j] = '0';
			j++;
		}
		map[i][width] = '\0';
		i++;
	}
	map[height] = NULL;
	return (map);
}

static char	**create_small_map(void)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 11)
	{
		map[i] = NULL;
		i++;
	}
	map[0] = strdup("1111111111");
	map[1] = strdup("1000000001");
	map[2] = strdup("1000010001");
	map[3] = strdup("1000100001");
	map[4] = strdup("1000100001");
	map[5] = strdup("1001S00001");
	map[6] = strdup("1000000001");
	map[7] = strdup("1000100001");
	map[8] = strdup("1000000001");
	map[9] = strdup("1111111111");
	map[10] = NULL;
	i = 0;
	while (i < 10)
	{
		if (!map[i])
		{
			j = 0;
			while (j < i)
			{
				free(map[j]);
				j++;
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

static char	**create_very_small_map(void)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * 4);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		map[i] = NULL;
		i++;
	}
	map[0] = strdup("111");
	map[1] = strdup("1N1");
	map[2] = strdup("111");
	map[3] = NULL;
	i = 0;
	while (i < 3)
	{
		if (!map[i])
		{
			j = 0;
			while (j < i)
			{
				free(map[j]);
				j++;
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

static char	**initialize_game_map(t_game *game, int choosed_size_map)
{
	t_player	*player;
	char		**map;
	int			player_count;
	int			i;
	int			j;

	player = &game->player;
	if (choosed_size_map == 1)
	{
		map = create_very_small_map();
		if (!map)
			return (NULL);
		game->map.width = 3;
		game->map.height = 3;
	}else if (choosed_size_map == 0)
	{
		map = create_small_map();
		if (!map)
			return (NULL);
		game->map.width = 10;
		game->map.height = 10;
	} else if (choosed_size_map == 2)
	{
		game->map.width = 100;
		game->map.height = 100;
		map = generate_map(game->map.width, game->map.height);
		if (!map)
			return (NULL);
	}
	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->x = j;
				player->y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Error\nThere must be exactly one player start \
				position (N, S, E, W).\n");
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
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


/*
** Loads a texture from an XPM file into the MLX image system.
** ----------------------------------------------------------------------------
** @param game: The game state containing MLX pointers
** @param texture: Pointer to the texture structure to fill
** @param path: Path to the XPM file to load
** @return: 0 on success, 1 on failure
*/

static int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (0);
}

static void	build_texture_path(char *dest, const char *type, const char *direction)
{
	strcpy(dest, "textures/");
	strcat(dest, type);
	strcat(dest, "/");
	strcat(dest, direction);
	strcat(dest, ".xpm");
}

static int	load_textures(t_game *game, char *type)
{
	char	north_path[100];
	char	south_path[100];
	char	east_path[100];
	char	west_path[100];

	build_texture_path(north_path, type, "NO");
	build_texture_path(south_path, type, "SO");
	build_texture_path(east_path, type, "EA");
	build_texture_path(west_path, type, "WE");
	if (load_texture(game, &game->map.textures[TEX_NORTH], north_path)
		|| load_texture(game, &game->map.textures[TEX_SOUTH], south_path)
		|| load_texture(game, &game->map.textures[TEX_EAST], east_path)
		|| load_texture(game, &game->map.textures[TEX_WEST], west_path))
	{
		printf("Error: loading %s textures failed\n", type);
		return (1);
	}
	return (0);
}

int	setup_game_environment(t_game *game, int choosed_texture, int choosed_size_map)
{
	if (init_mlx_components(game))
		return (1);
	game->map.map = initialize_game_map(game, choosed_size_map);
	if (!game->map.map)
		return (printf("Error: map initialization failed\n"), 1);
	init_player(game);
	game->map.floor_color[0] = 220;
	game->map.floor_color[1] = 100;
	game->map.floor_color[2] = 0;
	game->map.ceiling_color[0] = 225;
	game->map.ceiling_color[1] = 30;
	game->map.ceiling_color[2] = 0;
	if (choosed_texture == 0)
	{
		if (load_textures(game, "minecraft"))
			return (1);
	}
	else if (choosed_texture == 1)
	{
		if (load_textures(game, "cardinal"))
			return (1);
	}
	game->player.game = game;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized successfully\n");
	return (0);
}
