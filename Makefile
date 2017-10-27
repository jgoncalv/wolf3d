# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbuhler <nbuhler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/05 11:54:09 by nbuhler           #+#    #+#              #
#    Updated: 2017/10/27 14:39:54 by jgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./libft/include/

GCC_FLGS = -Werror -Wextra -Wall -g
MLX = -L mlx -lmlx -framework OpenGL -framework AppKit

SRC_NAME = main.c parser.c error_message.c init.c raycasting.c keyhook.c\
 draw_ray.c loophook.c draw.c put_pxl.c draw_minimap.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L,$(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	$(CC) $(GCC_FLGS) $(MLX) $(LIB) -lft $(INC) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(GCC_FLGS) -MMD -c $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	rm -fv $(NAME)

re: fclean all

.PHONY:			fclean clean re relib cleanlib fcleanlib

-include $(OBJ:.o=.d)
