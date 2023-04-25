CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp Bureaucrat.cpp AForm.cpp PresidentialPardonForm.cpp \
		ShrubberyCreationForm.cpp RobotomyRequestForm.cpp

NAME = no_need

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
