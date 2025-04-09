# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 10:08:43 by jhapke            #+#    #+#              #
#    Updated: 2025/04/08 14:27:10 by jhapke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCE =	algorithm.c\
		isometric.c\
		main.c\
		errors.c\
		mlx_management.c\
		parsing.c\
		memory.c\
		visual.c\

GNL_DIR = get_next_line
GNL_SRC = $(GNL_DIR)/get_next_line.c\
		$(GNL_DIR)/get_next_line_utils.c\

OBJS = $(SOURCE:.c=.o) $(GNL_SRC:.c=.o)

FLAGS = -Werror -Wall -Wextra
CC = gcc

HEADER = fdf.h
GNL_HEADER = $(GNL_DIR)/get_next_line.h

LIBFT_DIR = libft
LIBFT_H = $(LIBFT_DIR)/libft.h
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_A = $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS = -ldl -lglfw -pthread -lm

INCLUDES = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX42_DIR)/include

all: $(MLX42_A) $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX42_A)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) $(MLX42_A) -o $(NAME) $(MLX42_FLAGS)

%.o: %.c $(HEADER) $(GNL_HEADER) $(LIBFT_H)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(MLX42_A):
	mkdir -p $(MLX42_DIR)/build
	cd $(MLX42_DIR)/build && cmake .. && make

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	@if [ -d $(MLX42_DIR)/build ]; then \
		make -C $(MLX42_DIR)/build clean 2>/dev/null || true; \
	fi

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	@if [ -d $(MLX42_DIR)/build ]; then \
		rm -rf $(MLX42_DIR)/build; \
	fi

re: fclean all

.PHONY: all clean fclean re