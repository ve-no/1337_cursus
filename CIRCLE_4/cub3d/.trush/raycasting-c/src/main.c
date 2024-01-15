/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:08:30 by ibouchaf          #+#    #+#             */
/*   Updated: 2023/07/08 09:40:14 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int	distroy_event(int keycode, t_cub *cub)
{
	(void)cub;
	(void)keycode;
	exit(0);
	return (0);
}

int	mapHasWallAt(float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;
	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT
		|| x >= WINDOW_WIDTH )
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}

unsigned int get_pixel_from_image(t_img *img, int x, int y)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;
	if (x < 0 || y < 0 || y >= WINDOW_HEIGHT
		|| x >= WINDOW_WIDTH)
		return ;
	dst = img->addr + (y * (MAP_NUM_COLS * TILE_SIZE * 4) + x * 4);
	*(unsigned int *)dst = color;
}

float normalizeAngle(float angle) {
    angle = remainder(angle, TWO_PI);
    if (angle < 0) {
        angle = TWO_PI + angle;
    }
    return angle;
}

void	my_pixel_put(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(cub->img, (x + i) * MINIMAP_SCALE, (y + j) * MINIMAP_SCALE, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_cub *cub)
{
	int		i;
	int		j;
	int		tilex;
	int		tiley;

	j = 0;
	while (j < MAP_NUM_ROWS)
	{
		i = 0;
		while (i < MAP_NUM_COLS)
		{
			tilex = i * TILE_SIZE;
			tiley = j * TILE_SIZE;
			if (map[j][i] == 1)
				my_pixel_put(cub, tilex, tiley, 0xDFCD8B);
			else
				my_pixel_put(cub, tilex, tiley, 0xB1B3B2);
			i++;
		}
		j++;
	}
}

// void	draw_line(t_cub *cub, int beginx, int beginy,
// 					int endx, int endy, int color)
// {
// 	int		pixels;
// 	double	pixelx;
// 	double	pixely;
// 	double	deltax;
// 	double	deltay;

// 	deltax = endx - beginx;
// 	deltay = endy - beginy;
// 	pixels = sqrt((deltax * deltax) + (deltay * deltay));
// 	deltax /= pixels;
// 	deltay /= pixels;
// 	pixelx = beginx;
// 	pixely = beginy;
// 	while (pixels)
// 	{
// 		my_mlx_pixel_put(cub->img, pixelx * MINIMAP_SCALE, pixely * MINIMAP_SCALE, color);
// 		pixelx += deltax;
// 		pixely += deltay;
// 		--pixels;
// 	}
// }

void	render_player(t_cub *cub)
{

	my_mlx_pixel_put(cub->img, cub->player->x * MINIMAP_SCALE, cub->player->y * MINIMAP_SCALE, 0x00203FFF);
	// draw_line(cub, cub->player->x, cub->player->y,
	// 	cub->player->x + cos(cub->player->angle) * 70,
	// 	cub->player->y + sin(cub->player->angle) * 70, 0x00203FFF);
}

void	move_player(t_cub *cub)
{
	float	move_step;
	float	new_px;
	float	new_py;

	cub->player->angle += cub->player->turndir * cub->player->turnspeed;
	move_step = cub->player->walkdir * cub->player->walkspeed;
	new_px = cub->player->x + cos(cub->player->angle) * move_step;
	new_py = cub->player->y + sin(cub->player->angle) * move_step;

	if (!mapHasWallAt(new_px, cub->player->y))
		cub->player->x = new_px;
	if (!mapHasWallAt(cub->player->x, new_py))
		cub->player->y = new_py;

}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == W_KEY || keycode == UP_KEY)
		cub->player->walkdir = 1;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = -1;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		cub->player->turndir = 1;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = -1;
	// move_player(cub);
	return (0);
}

int	set_defeult(int keycode, t_cub *cub)
{
	if (keycode == W_KEY || keycode == UP_KEY
		|| keycode == S_KEY || keycode == DOWN_KEY)
		cub->player->walkdir = 0;
	else if (keycode == D_KEY || keycode == RIGHT_KEY
		|| keycode == A_KEY || keycode == LEFT_KEY)
		cub->player->turndir = 0;
	return (0);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_ray(float rayAngle, int stripId, t_ray **rays, t_cub *cub) {
	rayAngle = normalizeAngle(rayAngle);

	int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	int foundHorzWallHit = FALSE;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = cub->player->x + (yintercept - cub->player->y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorzWallHit = TRUE;
			break;
		} else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	int foundVertWallHit = FALSE;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = cub->player->y + (xintercept - cub->player->x) * tan(rayAngle);

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = TRUE;
			break;
		} else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	// Calculate both horizontal and vertical hit distances and choose the smallest one
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(cub->player->x, cub->player->y, horzWallHitX, horzWallHitY)
		: INT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(cub->player->x, cub->player->y, vertWallHitX, vertWallHitY)
		: INT_MAX;

	if (vertHitDistance < horzHitDistance) {
		rays[stripId]->distance = vertHitDistance;
		rays[stripId]->wallhitX = vertWallHitX;
		rays[stripId]->wallhitY = vertWallHitY;
		rays[stripId]->wallHitContent = vertWallContent;
		rays[stripId]->wasHitVertical = TRUE;
	} else {
		rays[stripId]->distance = horzHitDistance;
		rays[stripId]->wallhitX = horzWallHitX;
		rays[stripId]->wallhitY = horzWallHitY;
		rays[stripId]->wallHitContent = horzWallContent;
		rays[stripId]->wasHitVertical = FALSE;
	}
	rays[stripId]->rayAngle = rayAngle;
	rays[stripId]->is_facing_down = isRayFacingDown;
	rays[stripId]->is_facing_up = isRayFacingUp;
	rays[stripId]->is_facing_left = isRayFacingLeft;
	rays[stripId]->is_facing_right = isRayFacingRight;
}


void	cast_all_rays(t_cub *cub)
{
	float rayAngle = cub->player->angle - (FOV_ANGLE/ 2);
	int	stripid = 0;

	while (stripid < NUM_RAYS)
	{
		cast_ray(rayAngle, stripid, cub->ray, cub);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		stripid++;
	}
}


void init_texture(t_cub *cub, int i)
{
	cub->texture = malloc(sizeof(t_img));
	if (cub->ray[i]->is_facing_down)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx, "./pikuma.xpm", &cub->texture->width, &cub->texture->height);
	else if (cub->ray[i]->is_facing_up)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx, "./graystone.xpm", &cub->texture->width, &cub->texture->height);
	else if (cub->ray[i]->wasHitVertical)
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx, "./redbrick.xpm", &cub->texture->width, &cub->texture->height);
	else
		cub->texture->img = mlx_xpm_file_to_image(cub->data->mlx, "./wood.xpm", &cub->texture->width, &cub->texture->height);

	if (!cub->texture->img)
		exit(0);
	cub->texture->addr = mlx_get_data_addr(cub->texture->img, &cub->texture->bits_per_pixel,
			&cub->texture->line_length, &cub->texture->endian);
}

void rect(t_cub *cub, int x, int y, int width, int height)
{
	int i;
	int j;
	int tex_x;
	int tex_y;
	float scale1;
	float scale2;

	i = 0;
	scale1 = cub->texture->width / TILE_SIZE;
	tex_x = cub->ray[x]->wallhitX;
	if(cub->ray[x]->wasHitVertical)
		tex_x = cub->ray[x]->wallhitY;
	tex_x = fmod((tex_x * scale1), cub->texture->width);
	scale2 = ((double)cub->texture->height / height);
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			if ((y + j) >= WINDOW_HEIGHT)
				break;
			tex_y = j * scale2;
			// printf("%c\n", map[i][j]);
			my_mlx_pixel_put(cub->img, x + i, y + j, get_pixel_from_image(cub->texture, tex_x, tex_y));
			j++;
		}
		i++;
	}
}

void generate3DProjection(t_cub *cub, t_ray **rays)
{
	for (int i = 0; i < NUM_RAYS; i++) {
		float perpDistance = rays[i]->distance * cos(rays[i]->rayAngle - cub->player->angle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		// wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		// init_texture(cub, i);
		rect(cub, i * WALL_STRIP_WIDTH, wallTopPixel, 1, wallStripHeight);
	}

}

void clear_sceen(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(cub->img, i, j, 0);
			j++;
		}
		i++;
	}
}

int	setup(t_cub *cub)
{
	clear_sceen(cub);
	// render_map(cub);
	// render_player(cub);
	move_player(cub);
	cast_all_rays(cub);
	generate3DProjection(cub, cub->ray);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->img->img, 0, 0);
	return 0;
}


void	initialize(t_cub *cub)
{
	int i = -1;
	cub->data = malloc(sizeof(t_data));
	cub->player = malloc(sizeof(t_player));
	while (i < NUM_RAYS)
		cub->ray[i++] = malloc(sizeof(t_ray));
	if (!cub->data || !cub->player)
		exit_strerr("malloc", errno);
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		exit_error("mlx_init", "Error initializing MLX");
	cub->data->win = mlx_new_window(cub->data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->data->win)
		exit_error("mlx_new_window", "Error creating MLX window");
	cub->img = malloc(sizeof(t_img));
	if (!cub->img)
        exit_strerr("malloc", errno);
	cub->img->img = mlx_new_image(cub->data->mlx, WINDOW_WIDTH
	, WINDOW_HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
			&cub->img->line_length, &cub->img->endian);
	init_texture(cub, 0);
}

int main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		exit_success("Usage: ./cub3D <map.cub>");
	cub = (t_cub *)malloc(sizeof(t_cub));
    parsing(av[1]);
    initialize(cub);
	cub->player->x = WINDOW_WIDTH / 2;
	cub->player->y = WINDOW_HEIGHT / 2;
	cub->player->angle = PI / 2;
	cub->player->turndir = 0;
	cub->player->walkdir = 0;
	cub->player->turnspeed = 8 * (PI / 180);
	cub->player->walkspeed = 40;
	mlx_hook(cub->data->win, 2, 0, key_hook, cub);
	mlx_hook(cub->data->win, 3, 0, set_defeult, cub);
	mlx_hook(cub->data->win, 17, 0, distroy_event, cub);
	mlx_loop_hook(cub->data->mlx, setup, cub);
	mlx_loop(cub->data->mlx);
}
