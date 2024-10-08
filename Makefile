# Değişkenler
NAME := ircserv
BOT_NAME := turco
SRC_DIR := src
BOT_DIR := bot
OBJ_DIR := obj
BOT_OBJ_DIR := $(BOT_DIR)/obj
INC_DIR := include
SRC := $(wildcard $(SRC_DIR)/*.cpp)
BOT_SRC := $(wildcard $(BOT_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BOT_OBJ := $(BOT_SRC:$(BOT_DIR)/%.cpp=$(BOT_OBJ_DIR)/%.o)
INC := -I$(INC_DIR)

# Derleyici ve Derleme Seçenekleri
CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -g

# Hedefler
all: $(NAME)

$(BOT_NAME): $(BOT_OBJ)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BOT_OBJ_DIR)/%.o: $(BOT_DIR)/%.cpp | $(BOT_OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BOT_OBJ_DIR):
	mkdir -p $(BOT_OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BOT_OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(BOT_NAME)

re: fclean all

.PHONY: all clean fclean re
