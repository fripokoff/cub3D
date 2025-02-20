#include "../includes/cub3d.h"

void init_player(t_game *game)
{
	int player_x = game->player.pos_x;
	int player_y = game->player.pos_y;
	if(game->map[player_y][player_x] == 'N')
	{
		game->player.angle = 3 * PI/2;
	}else if (game->map[player_y][player_x] == 'S')
	{
		game->player.angle = PI / 2;
	}else if (game->map[player_y][player_x] == 'E')
	{
		game->player.angle = PI / 0;
	}
	else if (game->map[player_y][player_x] == 'W')
	{
		game->player.angle = PI / 1;
	}
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

int key_press(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if(keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return 0;
}

int key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if(keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return 0;
}