## Compile and Run

### For clone and compile mlx
```bash
make mlx
```
### For compile program 
```bash
make
```
### Run the program
```bash
./cub3D
```

## Norm
```bash
./make norm
```
```
➜  cub3D git:(main) make norm                                 
norminette includes/cub3d.h
includes/cub3d.h: OK!
norminette src/*
src/main.c: OK!
src/map/init.c: Error!
Error: TOO_MANY_LINES       (line:  64, col:   1):      Function has more than 25 lines
src/player/player.c: OK!
src/player/movement.c: OK!
src/ray/env_render.c: OK!
src/ray/ray_utils.c: OK!
src/ray/ray_casting.c: OK!
make: *** [Makefile:37: norm] Error 1
```

### Choose map
- Cardinal map = 0
- Wolf map = 1
```bash
./cub3D 0
```
