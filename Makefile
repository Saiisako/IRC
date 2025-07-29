NAME = a.out

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address,leak

RM = rm -rf

SRCS =	main.cpp\

OBJS = $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo Compiling..
	@sleep 0.8
	@echo success !

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo File Erased !

re: fclean all

.PHONY: all clean fclean re