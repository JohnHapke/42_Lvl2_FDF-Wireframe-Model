# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 10:08:43 by jhapke            #+#    #+#              #
#    Updated: 2025/06/21 17:02:46 by jhapke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_DIR = src
PAR_DIR = $(SRC_DIR)/parsing
ALG_DIR = $(SRC_DIR)/algorithm
GRA_DIR = $(SRC_DIR)/graphics
MLX_DIR = $(SRC_DIR)/mlx_handling
UTILS_DIR = $(SRC_DIR)/utils
GNL_DIR = get_next_line

SOURCE =	$(SRC_DIR)/main.c\
			$(PAR_DIR)/parse_file.c\
			$(PAR_DIR)/parse_map.c\
			$(PAR_DIR)/parsing_handler.c\
			$(ALG_DIR)/bresenham.c\
			$(ALG_DIR)/handling_algorithm.c\
			$(ALG_DIR)/isometric_calc.c\
			$(GRA_DIR)/map_colors.c\
			$(GRA_DIR)/map_projection.c\
			$(MLX_DIR)/mlx_handler.c\
			$(MLX_DIR)/mlx_hooks.c\
			$(MLX_DIR)/mlx_rendering.c\
			$(UTILS_DIR)/errors.c\
			$(UTILS_DIR)/memory.c\
			$(GNL_DIR)/get_next_line.c\
			$(GNL_DIR)/get_next_line_utils.c\

OBJS = $(SOURCE:.c=.o)

FLAGS = -Werror -Wall -Wextra -g #-fsanitize=address
CC = gcc

LIBFT = libft/libft.a
MLX42_DIR = MLX42
MLX42_A = $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS = -ldl -lglfw -pthread -lm

INCLUDES = -Iinclude -Ilibft -Iget_next_line -IMLX42/include

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_A)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX42_A) -o $(NAME) $(MLX42_FLAGS)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX42_A):
	mkdir -p MLX42/build
	cd MLX42/build && cmake .. && make

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	rm -rf MLX42/build

re: fclean all

.PHONY: all clean fclean re