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

# Colors for messages
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

all: 
	@make mlx $(NAME) --no-print-directory
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣴⣾⣿⣿⣷⣦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠰⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠆⠀⠀⠀\n"
	@printf "⠀⠀⢸⣷⣦⣈⠙⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠋⣁⣴⣾⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣷⣦⣄⣉⠛⠻⢿⣿⣿⡿⠟⠛⣉⣠⣴⣾⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡌⢡⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\n"
	@printf "⠀⠀⠘⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠃⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠉⠛⠿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⠿⠛⠉⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠿⣿⡇⢸⣿⠿⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "$(RED)C U B E 3 D  C O M P I L E D$(NC)\n"
	@printf "    @the01rch 🤝 @fripok\n"

mlx:
	@if [ ! -d "./includes/mlx" ]; then \
		printf "$(BLUE)[MINILIBX]$(NC)\n"; \
		printf "$(BLUE)⌛ Installing minilibx...$(NC)\n"; \
		git clone -q https://github.com/42Paris/minilibx-linux.git ./includes/mlx && \
		printf "  └$(BLUE)⚙️ Compiling minilibx...$(NC)\n"; \
		make -C ./includes/mlx > /dev/null 2>&1 && \
		printf "    └$(GREEN)✅ minilibx installed!$(NC)\n"; \
	elif [ ! -f "./includes/mlx/libmlx.a" ]; then \
		printf "$(BLUE)⚙️  Compiling minilibx...$(NC)\n"; \
		make -C ./includes/mlx > /dev/null 2>&1 && \
		printf "$(GREEN)✅ minilibx compiled!$(NC)\n"; \
	fi

%.o: %.c
	@printf "\033[2K\r$(BLUE)⌛ Compilation:$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): 
	@printf "\n$(BLUE)[CUB3D]$(NC)\n"
	@make $(OBJ) --no-print-directory
	@printf "\n  └$(BLUE)⚙️  Linking $(NAME)...$(NC)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INCLUDES) $(LFLAGS)
	@printf "   └$(GREEN)✅ $(NAME) created!$(NC)\n"

clean:
	@printf "\n🗑️  Removing object files...\n"
	@rm -rf $(OBJ)
	@if [ -d "./includes/mlx" ]; then \
		printf "$(YELLOW)🧹 Cleaning mlx$(NC)\n"; \
		make clean -C includes/mlx > /dev/null 2>&1; \
		printf "  └$(GREEN)✅ mlx cleaned!$(NC)\n"; \
	fi
	@printf "$(GREEN)✅ Cleaning completed!$(NC)\n\n"

norm:
	@printf "$(BLUE)📋 Checking norm...$(NC)\n"
	@norminette includes/cub3d.h
	@norminette src/*
	@printf "$(GREEN)✅ Check completed!$(NC)\n"

fclean: clean
	@printf "🗑️  Removing the executable $(NAME)...\n"
	@rm -rf $(NAME)
	@printf "  └$(GREEN)✅ Exectuabe removed!$(NC)\n"
	@printf "\n🗑️  Removing the mlx...\n"
	@rm -rf ./includes/mlx
	@printf "  └$(GREEN)✅ mlx removed!$(NC)\n"
	@printf "\n$(GREEN)✅ Full cleaning completed!$(NC)\n\n"

re: fclean all

.PHONY: all clean fclean re mlx