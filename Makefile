# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 23:02:51 by asimoes           #+#    #+#              #
#    Updated: 2021/12/30 00:56:58 by asimoes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=so_long
SRCS=srcs/draw.c\
	srcs/free.c\
	srcs/main.c\
	srcs/map.c\
	srcs/textures.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c
OBJS=${SRCS:.c=.o}
CC=cc
MLX=minilibx-linux/libmlx.a
LFT=libft/libft.a
CFLAGS=-Wall -Wextra -Werror -I. -Iincludes -Imlx
CLIBS=-lXext -lX11 -Lminilibx-linux -lmlx_Linux -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLIBS)

$(NAME): $(OBJS) $(LFT) $(MLX) includes/solong.h
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)

$(LFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re