#include "clone.h"
#include "event.c"
#include "load_texture.c"

void draw(t_info *info)
{
	for(int y = 0; y < height; y ++)
	{
		for(int x = 0; x < width; x ++)
			info->img.data[y * width + x] = info->buf[y][x];
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void calc(t_info *info)
{
	//천장과 바닥을 화면의 반반쪼개서 색을 먼저 칠해놓음
	//이때 색은 추후에 받는 색으로 변경예정
	for(int i = 0; i < 480; i ++)
	{
		for(int j = 0; j < 640; j ++)
		{
			if(i < 240)
				info->buf[i][j] = (255 << 8);
			else
				info->buf[i][j] = 255;
		}
	}

	//모든 width(화면의 가로)에 대해서 반복
	//매 반복마다 해당 x의 y값이 모두 결정됨
	//배경색(천장, 바닥)은 모두 칠해져 있으므로 벽만 칠하면 성공
	for(int x = 0; x < width; x ++)
	{
		//이번 반복의 표현할 x값임 화면에서 가장 왼쪽이면 -1 중간이면 0 오른쪽이면 1
		//x값에서 나와 처음 만나는 물체의 거리를 바탕으로 y값도 결정할수있음
		double cameraX = 2 * x / (double)width - 1;
		//rayDir은 내 위치에서 지금 찍고자 하는 카메라로의 방향벡터
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//내가 처음 만나는 x, y
		double sideDistX;
		double sideDistY;

		//sideDist가 검사할 다음 벽은 deltaDist를 더해서 찾음
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(worldMap[mapX][mapY] == '1')
			{
				hit = 1;
			}
		}
		if(side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		
		int lineHeight = (int)(height / perpWallDist);
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;
		int texNum = 0;
		if(side == 0)
		{
			if(rayDirX < 0) //south (wood)
				texNum = 2;
			else
				texNum = 3; //north (red)
		}
		else
		{
			if(rayDirY < 0) //east (purple)
				texNum = 0;
			else
				texNum = 1; //west (stone)
		}
		double wallX;
		if(side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
		
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = info->texture[texNum][texY][texX];
			if(side == 1)
				color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
		}
	}
}


int main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return 0;
}

void get_map()
{
	int fd = open("map.cub", O_RDONLY);
	int i = 0;
	// while(1)
	// {
	// 	char *str;
	// }
	// while(1)
	// {
	// 	char *str;
	// }
	// i = 0;
	while(1)
	{
		char *str = get_next_line(fd);
		if(str == NULL)
			break;
		worldMap[i++] = str;
	}
	worldMap[i] = NULL;
	close(fd);
}

int main()
{
	t_info info;
	get_map();

	info.mlx = mlx_init();
	info.posX = 11.0;
	info.posY = 27.0;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;

	info.moveSpeed = 0.15;
	info.rotSpeed = 0.1;
	for(int i = 0; i < height; i ++)
	{
		for(int j = 0; j < width; j ++)
			info.buf[i][j] = 1;
	}
	//texture을 불러와 2차원배열 형태로 저장함
	load_texture(&info);

	info.win = mlx_new_window(info.mlx, width, height, "mlx");
	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 17, 0, redcross, NULL);
	mlx_loop(info.mlx);
}
