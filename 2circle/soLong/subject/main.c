// #include <mlx.h>
#include "mlx/mlx.h"
#include <stdio.h>

// typedef struct s_data{
// 	void *img;
// 	char *addr;
// 	int bits_per_pixel;
// 	int line_length;
// 	int endian;
// }	t_data;

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// }				t_vars;

// int key_hook(int keycode, t_vars *vars)
// {
// 	printf("Hello from key_hook!\n");
// 	printf("keycode : %d\n", keycode);
// 	return (0);
// }

// int close(int keycode, t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	return (0);
// }


// void my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char *dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)) ;
// 	*(unsigned int *)dst = color ;
// }

// void make_circle(int x, int y, int radius, t_data *img)
// {
// 	for(int i = x - radius; i < x + radius; i ++)
// 	{
// 		for(int j = y - radius; j < y + radius; j ++)
// 		{
// 			if(((x - i) * (x - i) + (y -j) * (y - j)) <= (radius * radius))
// 				my_mlx_pixel_put(img, i, j, 0x00FF0000);
// 		}
// 	}
// }

int main()
{

	// t_vars	vars;
	// t_data img;

	// char *relative_path = "./asset/pocketmon_front.xpm";

	// vars.mlx = mlx_init(); //현재 mlx인스턴스위치 가진 포인터 반환 software과 display 연결
	// vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!"); //윈도우에 대한 포인터 반환
	
	//이미지를 저장할 수 있는 공간 할당
	// img.img = mlx_new_image(vars.mlx, 1920, 1080); //이미지생성 하지만 무언가를 보여주려면 픽셀을 써야함
	// //생성된 img에 대한 정보 알려주는 함수
	// img.addr = mlx_get_data_addr(img.img, 
	// 	&img.bits_per_pixel, &img.line_length, &img.endian); //이미지를 주면 적절한 값 얻어옴
	// printf("img.img : %p\n", img.img);
	// printf("img.addr : %p\n", img.addr);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); //5 5 위치에 빨간색 점 하나 찍음
	//make_circle(960, 540, 400, &img);
	// for(int i = 50; i < 151; i ++)
	// {
	// 	for(int j = 50; j < 151; j ++)
	// 	{
	// 		if(((100 - i) * (100 - i) + (100 -j) * (100 - j)) <= (50 * 50))
	// 			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
	// 	}
	// }
	void	*mlx;
	void	*win;
	void	*img;
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "putImage");
	img = mlx_xpm_file_to_image(mlx, "asset/pocketmon_front.xpm", &img_width, &img_height);
    //xpm 파일을 불러와 이미지로 변환하고 img에 저장해줌
	mlx_put_image_to_window(mlx, win, img, 0, 0);
    // xpm에서 이미지로 변환한 img를 화면에 (50,50)위치에 띄워줌
	mlx_loop(mlx);
	return (0);
}
