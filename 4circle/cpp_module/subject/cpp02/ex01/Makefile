CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp Fixed.cpp

NAME = useful_fixed_point

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

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
