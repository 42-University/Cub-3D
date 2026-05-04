# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkenji-u <tkenji-u@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/24 17:57:39 by tkenji-u          #+#    #+#              #
#    Updated: 2026/04/24 18:07:51 by tkenji-u         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
MLX_FLAGS   = -lmlx -framework OpenGL -framework AppKit -lm

SRC_DIR     = src
INC_DIR     = include
OBJ_DIR     = obj
LIBFT_DIR   = libft

SRC_FILES   = main.c \
              parsing/parse_config.c \
              parsing/parse_map.c \
              utils/utils.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INC         = -I $(INC_DIR) -I $(LIBFT_DIR)

LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

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

.PHONY: all clean fclean re bonus