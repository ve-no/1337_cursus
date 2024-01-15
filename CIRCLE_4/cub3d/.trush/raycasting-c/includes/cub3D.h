/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:43:27 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/07 10:45:07 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
#include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define ESC_KEY 53
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125

# define PI 3.14159265359
# define TWO_PI 6.28318530718

#define MINIMAP_SCALE_FACTOR 0.5

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))
# define MINIMAP_SCALE 0.2
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	int		turndir;
	int		walkdir;
	float	turnspeed;
	float	walkspeed;
}	t_player;

typedef struct s_data {
	void	*mlx;
	void	*win;

}	t_data;


typedef struct s_ray {
	float	rayAngle;
	float	wallhitX;
	float	wallhitY;
	float	distance;
	int		wallHitContent;
	int		wasHitVertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
}	t_ray;

typedef struct s_cub {
	t_data		*data;
	t_player	*player;
	t_img		*img;
	t_img		*texture;
	t_ray		*ray[NUM_RAYS];
	char		**map;
}	t_cub;

void	parsing(char *str);
void	file_checker(char *str);

void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

void	render_map(t_cub *cub);
void	render_player(t_cub *cub);

#endif
