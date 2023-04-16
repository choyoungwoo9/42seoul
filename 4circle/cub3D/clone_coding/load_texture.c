#include "clone.h"

void load_image(t_info *info, int texture[][64], char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for(int y = 0; y < img->img_height; y ++)
	{
		for(int x = 0; x < img->img_width; x ++)
			texture[y][x] = img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
}


void load_texture(t_info *info)
{
	t_img img;

	load_image(info, info->texture[0], "textures/wood.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);	
}