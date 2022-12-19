rm -f a.out
cc -L./mlx -lmlx -framework OpenGL -framework AppKit main.c
# cc -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit main.c
./a.out
# gcc *.c -I. -Lmlx -lmlx -framework OpenGL -framework Appkit
#-frameword OpenGL -framework AppKit -lz