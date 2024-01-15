/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:43:27 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/25 14:49:41 by ael-bako         ###   ########.fr       */
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
# include <limits.h>
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

# define MINIMAP_SCALE_FACTOR 1

# define TILE_SIZE 64

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 820
// 60 * (PI / 180)
# define FOV_ANGLE 1.047
# define MINIMAP_SCALE 0.25
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS WINDOW_WIDTH

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_sprites
{
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}	t_sprites;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		turndir;
	int		walkspeed;
	float	turnspeed;
	float	vertical;
	float	horizontal;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*win;

}	t_data;

typedef struct s_ray
{
	float	ray_angle;
	float	wallhit_x;
	float	wallhit_y;
	float	distance;
	int		wall_hit_content;
	int		was_hit_vertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
}	t_ray;

typedef struct s_mx
{
	char	**map;
	char	**map2;
	int		height;
	int		width;
	int		count;
	int		print;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	float	p_dir;
	char	*c;
	char	*f;
	int		color1;
	int		color2;
	int		i;
	int		j;
	float	x;
	float	y;
	int		map2_height;
}	t_mx;

typedef struct s_cub
{
	t_data		*data;
	t_player	*player;
	t_img		*img;
	t_img		*texture;
	t_sprites	*sprit;
	t_ray		*ray[NUM_RAYS];
	t_mx		*mx;
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
	float		horzwallhit_x;
	float		horzwallhit_y;
	int			horz_wall_content;
	float		vertwallhit_x;
	float		vertwallhit_y;
	int			vert_wall_content;
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;
}	t_cub;

void			parsing_map(t_mx *mlx, char *av);
void			if_edentifier_is_null(t_mx *mlx);
void			check_colors(t_mx *mlx);
int				check_identifier_extension(t_mx *mlx);
void			check_walls(t_mx *mlx);
int				is_facing(int facing);
int				set_defeult(int keycode, t_cub *cub);
int				key_hook(int keycode, t_cub *cub);
int				distroy_event(int keycode, t_cub *cub);
int				map_has_wall_at(float x, float y, t_cub *cub);
void			move_player(t_cub *cub);
void			generate_projection(t_cub *cub, t_ray **rays);
void			cast_all_rays(t_cub *cub);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	get_pixel_from_image(t_img *img, int x, int y);
float			find_vertical_wall_hit(t_ray **rays, int stripId, t_cub *cub);
void			calculate_vertical_intersection(float ray_angle, t_cub *cub);
void			calculate_horizontal_intersection(float ray_angle, t_cub *cub);
t_img			*get_dir(t_cub *cub, int x);
float			normalize_angle(float angle);
void			calculate_ray_direction(float ray_angle, t_cub *cub);
float			find_horizontal_wall_hit(t_ray **rays, int stripId, t_cub *cub);
void			check_extension(int ac, char *str);
int				rgb_to_decimal(char *s);
void			render_floor(t_cub *cub, int y, int width, int height);
void			render_ceiling(t_cub *cub, int y, int width, int height);
#endif
