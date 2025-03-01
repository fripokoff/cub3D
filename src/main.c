#include "../includes/cub3d.h"

int DEBUG;

void put_pixel(int x, int y, int color, t_game *game)
{
	if( x >=  WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >>16)  & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y , color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x , y + i , color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + size , y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size , color, game);
}

void draw_map(t_game *game)
{
	char **map = game->map;
	int color = BLUE_HEX;
	for(int y=0; map[y]; y++)
	{
		for(int x=0; map[y][x]; x++)
		{
			if(map[y][x] == '1')
				draw_square(x * WALL_SIZE, y * WALL_SIZE, WALL_SIZE,color,  game);
		}
	}
}

char **get_map(t_player *player)
{
	int map_size = 11;
	char **map = malloc(sizeof(char *) * map_size);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "10000000001S001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	int player_count = 0;
	int i = 0;
	int j = 0;
	while(i < map_size - 1)
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

int init_game(t_game *game)
{
	game->map = get_map(&game->player);
	init_player(game);
	if(!game->map)
		return 1;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cubi");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	game->player.game = game;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	printf("Game initialized\n");
	return 0;
}

bool touch(float px, float py, t_game *game)
{
	int x = px / WALL_SIZE;
	int y = py / WALL_SIZE;
	
	if(x < 0 || y < 0 || x >= strlen(game->map[0]) || y >= 10)
		return true;
	if(game->map[y][x] == '1')
		return true;
	return false;
}

void clear_image(t_game *game)
{
	for(int y=0; y < HEIGHT; y++)
		for(int x=0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}



float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	/* Correction fisheye */
	float dist = sqrt(delta_x * delta_x + delta_y * delta_y);
	float fix_dist = dist * cos(angle);
	/* Normaliser angle */
	angle = fmod(angle + 2 * PI, 2 * PI);
	if (angle > PI)
		angle -= 2 * PI;
	return fix_dist;
}


void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;
	float ray_step = 0.5;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0x0000FF, game);
		ray_x += cos_angle * ray_step;
		ray_y += sin_angle * ray_step;
	}
	if(!DEBUG)
	{
		int brightness = false;
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (WALL_SIZE * HEIGHT) / dist;
		height = fmin(height, HEIGHT * 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		start_y = fmax(0, start_y);
		end = fmin(HEIGHT - 1, end);
		int color_value = (int)(255 * (1.0 - fmin(dist / (WALL_SIZE * 8), 1.0)));
		if (!brightness)
			color_value = 255;
		color_value = fmin(255, fmax(0, color_value));
		int color = color_value;
		while (start_y <= end)
		{
			put_pixel(i, start_y, color, game);
			start_y++;
		}
	}

}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	if(DEBUG)
	{
		draw_square(player->x, player->y, 20, GREEN_HEX, game);
		draw_map(game);
	}
	float fraction = PI /3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int main (int ac, char **av)
{
	t_game game;

	DEBUG = 0;
	if(ac == 2)
	{
		if(strcmp(av[1], "debug") == 0)
			DEBUG = 1;
	}
	if(init_game(&game) == 1)
		return 1;
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return 0;
}