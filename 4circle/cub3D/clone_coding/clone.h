#ifndef CLONE
#define CLONE

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key_macos.h"
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct s_img
{
	void *img;
	int *data;
	int size_l;
	int bpp;
	int endian;
	int img_width;
	int img_height;
}	t_img;

typedef struct s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void *mlx;
	void *win;
	t_img img;
	int buf[height][width];
	int texture[4][64][64];
	double moveSpeed;
	double rotSpeed;
}	t_info;

char	*worldMap[16];

#endif