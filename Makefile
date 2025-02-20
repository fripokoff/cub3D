NAME = cub3D 
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = includes/mlx/libmlx.a
SRC = src/main.c src/player.c src/movement.c

all: mlx $(NAME)

mlx:
	@if [ ! -d "./includes/mlx" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx && \
		make -C ./includes/mlx; \
	elif [ ! -f "./includes/mlx/libmlx.a" ]; then \
		make -C ./includes/mlx; \
	fi

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

clean:
	rm -rf $(OBJ)
	@if [ -d "./includes/mlx" ]; then \
		make clean -C ./includes/mlx; \
	fi

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx