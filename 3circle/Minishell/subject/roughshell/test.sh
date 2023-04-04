#cc -g3 -fsanitize=address main.c -lreadline -L/Users/youngwch/.brew/opt/readline/lib -I/Users/youngwch/.brew/opt/readline/include

cc src/get_input/*.c src/input_parse/*.c src/print/*.c -lreadline -L/Users/youngwch/.brew/opt/readline/lib -I/Users/youngwch/.brew/opt/readline/include

