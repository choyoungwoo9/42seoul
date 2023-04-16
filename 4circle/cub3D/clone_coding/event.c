#include "clone.h"

int key_press(int key, t_info *info)
{
	if(key == K_W)
	{
		if(worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX += info->dirX * info->moveSpeed;
		if(worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] != '1')
			info->posY += info->dirY * info->moveSpeed;
	}
	if(key == K_S)
	{
		if(worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX -= info->dirX * info->moveSpeed;
		if(worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	if(key == K_A)
	{
		if(worldMap[(int)(info->posX - info->planeX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX -= info->planeX * info->moveSpeed;
		if(worldMap[(int)(info->posX)][(int)(info->posY - info->planeY * info->moveSpeed)] != '1')
			info->posY -= info->planeY * info->moveSpeed;
	}
	if(key == K_D)
	{
		if(worldMap[(int)(info->posX + info->planeX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX += info->planeX * info->moveSpeed;
		if(worldMap[(int)(info->posX)][(int)(info->posY + info->planeY * info->moveSpeed)] != '1')
			info->posY += info->planeY * info->moveSpeed;
	}
	if(key == K_AR_R)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	if(key == K_AR_L)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if(key == K_ESC)
		exit(0);
	return 0;
}

int redcross(int key_code, void *data)
{
	data = NULL;
	exit(0);
}
