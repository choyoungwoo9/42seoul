#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53

// #include <math.h>
// #include "mlx/mlx.h"
#include "libft/libft.h"

#include <mlx.h>

#include <stdio.h>

int deal_key(int key)
{
	printf("key : %d\n", key);
	return 0;
}

int main()
{
	//validate 검사 (파일 이름)
	//valid한 맵이라고 확신 후 각종 정보 만듬
	//loop start
	//-> key event 받아서 화면 바꾸는 방식
	//0, 1, W
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	void* image = mlx_new_image(mlx_ptr, 500, 500);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_key_hook(win_ptr, deal_key, (void *)0);

	mlx_loop(mlx_ptr);
}
