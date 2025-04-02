NAME = cub3D 
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = includes/mlx/libmlx.a
SRC = src/main.c \
		src/utils/clean.c \
		src/utils/mlx_utils.c \
		src/player/player.c \
		src/player/movement.c \
		src/ray/ray_casting.c \
		src/ray/env_render.c \
		src/ray/ray_utils.c \
		src/ray/dda.c \
		src/map/init.c \

all: mlx $(NAME)

mlx:
	@if [ ! -d "./includes/mlx" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx && \
		make -C ./includes/mlx; \
	elif [ ! -f "./includes/mlx/libmlx.a" ]; then \
		make -C ./includes/mlx; \
	fi

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

clean:
	rm -rf $(OBJ)
	@if [ -d "./includes/mlx" ]; then \
		make clean -C includes/mlx; \
	fi

norm:
	norminette includes/cub3d.h
	norminette src/*

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx