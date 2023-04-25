CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp Base.cpp A.cpp B.cpp C.cpp ft_util.cpp

NAME = identify

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
