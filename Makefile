# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboissel <vboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 17:11:05 by vboissel          #+#    #+#              #
#    Updated: 2019/01/24 16:18:18 by vboissel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGSMLIB = -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = ./libft/
LIBFT = ./libft/libft.a
SRC = $(wildcard ./sources/*.c)
HDR = $(wildcard ./headers/*.h)
INC = ./headers
INC_MLX = /usr/local/include

all : $(NAME)

$(NAME): $(SRC) $(HDR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $() $(FLAGSMLIB) -I $(INC) -I $(LIBFT_DIR) $(LIBFT) $(SRC) -o "$(NAME)"

clean :
	@(cd $(LIBFT_DIR) && $(MAKE) $@)

fclean : clean
	@(cd $(LIBFT_DIR) && $(MAKE) $@)
	@rm -f $(NAME)

re : fclean all

.phony : $(NAME)
