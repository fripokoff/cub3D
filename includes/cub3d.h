#ifndef CUB3D_H
#define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define BLUE_HEX 0x0000FF
# define GREEN_HEX 0x00FF00
# define WALL_SIZE 64
# define PLAYER_SPEED 3
# define PLAYER_ANG_SPEED 0.1
extern int DEBUG;

#define PI 3.14159265359

#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
typedef struct s_player
{
    float x;
    float y;
    float pos_x;
    float pos_y;
    float angle;
    struct s_game *game;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
    
} t_player;


typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    t_player player;
    char *data;
    int bpp;
    int size_line;
    int endian;
    char    **map;
} t_game;

void init_player(t_game *player);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
bool touch(float px, float py, t_game *game);
void move_player(t_player *player);


#endif