CC			= c++ -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
RM			= rm -rf
NAME		= ./CC			= c++ -Wall -Wextra -Werror -std=c++98
RM			= rm -rf
NAME		= ./ircserv
NAME_SHORT	= ircserv
INCS_DIR	= include
MAIN_INC	= -I$(INCS_DIR)
INCS		= $(shell find $(INCS_DIR) -type f -name "*.hpp")

SRCS_DIR 	= .
SRCS		= $(shell find $(SRCS_DIR) -type f -name "*.cpp")
OBJS_DIR 	= obj
OBJS		= $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SRCS))


_COLOR		= \033[32m
_BOLDCOLOR	= \033[32;1m
_RESET		= \033[0m
_CLEAR		= \033[0K\r\c
_OK			= [\033[32mOK\033[0m]

vpath %.cpp $(SRCS_DIR)

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "[..] $(NAME_SHORT)... compiling $*.cpp\r\c"
	@$(CC) $(MAIN_INC) -c $< -o $@
	@echo "$(_CLEAR)"

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	@$(CC) $(OBJS) $(MAIN_INC) -o $(NAME)
	@echo "$(_OK) $(NAME_SHORT) compiled"

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
