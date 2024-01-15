/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:22:21 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/17 11:47:01 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "../libft/inc/libft.h"
# include <limits.h>

# define WHT "\033[1;37m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"

// Keyboard keys codes
# define UP1	13
# define UP2	126
# define RIGHT1	2
# define RIGHT2	124
# define DOWN1	1
# define DOWN2	125
# define LEFT1	0
# define LEFT2	123
# define ESC	53

// size of image
# define SIZE	55

typedef struct s_valid
{
	int	wall;
	int	coins;
	int	exit;
	int	player;
	int	enemy;
}		t_valid;

typedef struct s_data
{
	int		height;
	int		width;
	char	**map;
	char	**c_map;
	int		fd;
	int		p_x;
	int		p_y;
	int		x;
	int		y;
	int		i;
	int		j;
	char	*line;
	char	*tmp;
	t_valid	*check;
}		t_data;

typedef struct s_program
{
	void	*mlx;
	void	*window;
	void	*sand;
	void	*player;
	void	*p_down;
	void	*p_up;
	void	*p_right;
	void	*p_left;
	void	*coins;
	void	*lock;
	void	*unlock;
	void	*wall;
	void	*enemy_0;
	void	*enemy_1;
	void	*enemy_2;
	void	*enemy_3;
	void	*enemy_4;
	void	*enemy_5;
	void	*enemy_6;
	int		t_coins;
	int		i_size;
	int		render;
	t_data	*data;
}			t_program;

int		write_err(int c, t_data *map);
void	search(t_data *data);
int		check_wall(t_data *map);
int		check_content_map(t_data *map, int i);
int		path_is_valid(char **map);
int		fill_matrix_and_check(t_data *data);
void	valid_path(char **map, int x, int y, char *s);
int		map(t_data *data, char *arg);

void	ft_sprite(t_program *ap);
int		key_hook_a(int keycode, t_program *ap);
void	moving(int key, t_program *ap);
int		showing_img(t_program *ap);
void	ft_mlx_string_put(t_program *ap, int mv);
void	ft_sprite_b(t_program *ap);
int		ft_animation(t_program *ap);
void	random_images(t_program *ap, int x, int y);
int	move_enemy(t_program *ap);

int		exit_program(t_program *ap);
void	rip_program(t_program *ap);
void	free_memory(t_program **ap);
int		ft_close(t_program *ap);
void	new_window(t_program *ap);
void	ft_mlx_string_put(t_program *ap, int mv);

#endif
