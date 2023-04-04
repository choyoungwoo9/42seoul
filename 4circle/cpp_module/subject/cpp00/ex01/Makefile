CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp PhoneBook.cpp Contact.cpp

NAME = phonebook

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
