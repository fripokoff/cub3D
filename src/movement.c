#include "../includes/game.h"

// static void rotate_left(t_game *game)
// {
// 	double ang_speed;
// 	double old_dir_x;

// 	ang_speed = PLAYER_ANG_SPEED;
// 	old_dir_x = player->x;
// }

void move_player(t_player *player)
{
	float angle_speed = 0.03;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	float next_x = player->x;
	float next_y = player->y;
	float margin = 2.0f; // Marge de collision

	// Rotation
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	// Calcul de la prochaine position
	if (player->key_up)
	{
		next_x = player->x + cos_angle * PLAYER_SPEED;
		next_y = player->y + sin_angle * PLAYER_SPEED;
	}
	if (player->key_down)
	{
		next_x = player->x - cos_angle * PLAYER_SPEED;
		next_y = player->y - sin_angle * PLAYER_SPEED;
	}
	if (player->key_left)
	{
		next_x = player->x + sin_angle * PLAYER_SPEED;
		next_y = player->y - cos_angle * PLAYER_SPEED;
	}
	if (player->key_right)
	{
		next_x = player->x - sin_angle * PLAYER_SPEED;
		next_y = player->y + cos_angle * PLAYER_SPEED;

	}

	// Vérification des collisions avec marge
	if (!touch(next_x + margin, next_y + margin, player->game) && 
		!touch(next_x - margin, next_y - margin, player->game) &&
		!touch(next_x + margin, next_y - margin, player->game) &&
		!touch(next_x - margin, next_y + margin, player->game))
	{
		player->x = next_x;
		player->y = next_y;
	}
}