# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/24 17:57:39 by tkenji-u          #+#    #+#              #
#    Updated: 2026/05/04 20:52:50 by tkenji-u         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
MLX_DIR     = minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRC_DIR     = src
INC_DIR     = include
OBJ_DIR     = obj
LIBFT_DIR   = libft

SRC_FILES   = main.c \
              parsing/parse_config.c \
              parsing/parse_map.c \
              utils/parser_utils.c \
              visual/renderer.c \
              visual/raycast.c \
              visual/draw.c \
              visual/texture.c \
              visual/events.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INC         = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@# ensure miniLibX headers exist
	@test -f $(MLX_DIR)/mlx.h || { \
		echo "miniLibX not found in $(MLX_DIR). Please clone and build it:"; \
		echo "  git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)"; \
		echo "  cd $(MLX_DIR) && make"; \
		exit 1; }
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "Executable removed."

re: fclean all

bonus: all

norm:
	@command -v norminette >/dev/null 2>&1 || { echo "norminette not found. Install with 'pip3 install norminette'"; exit 1; }
	@norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR)

valgrind:
	@command -v valgrind >/dev/null 2>&1 || { echo "valgrind not found. Install via your package manager."; exit 1; }
	@test -f $(NAME) || { echo "$(NAME) not found. Run 'make' first."; exit 1; }
	@valgrind --leak-check=full ./$(NAME) --harness

.PHONY: all clean fclean re bonus norm valgrind
