CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = src/main.cpp src/Zombie.cpp

NAME = Zombie

%.o : %.c
	$(CC) $(CFLAGS) -cpp $< -o $@

OBJS = ${SRCS:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY: all clean fclean re
