#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/04 17:58:46 by vprypesh          #+#    #+#              #
#    Updated: 2018/07/04 17:58:47 by vprypesh         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME = wolf3d
PATH_INC = ./libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

HEAD = includes/wolf3d.h

SRC =	src/wolf3d.c \
		src/image.c \
		src/add_funcs.c \
		src/read_map.c \
		src/ray_casting.c \
		src/texture_mapping.c \
		src/draw_line.c \
		src/mapp.c \
		src/parse_map.c \
		src/key_handler.c \
		src/sdl_sound.c

OBJDIR =./obj/
INCLUDES_LIB = -I libft/
INCLUDE_SDL2 = -I includes/SDL/SDL2.framework/Headers

INCLUDES_SDL2_IMAGE = -I includes/SDL/SDL2_image.framework/Headers

INCLUDES_SDL2_MIXER = -I includes/SDL/SDL2_mixer.framework/Headers

INCLUDES_SDL2_TTF = -I includes/SDL/SDL2_ttf.framework/Headers

SDL_FRAMEWORK = -F includes/SDL -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer

MLX_FRAMEWORK = -lft -lmlx -framework OpenGL -framework AppKit

INCLUDES = $(INCLUDES_LIB) $(INCLUDE_SDL2) $(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_MIXER) $(INCLUDES_SDL2_TTF) $()
OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

.PHONY : all clean
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HEAD)
	make -C libft/
	$(CC) -o $(NAME) $(OBJ) $(INCLUDES) -lm -L libft/  $(INCLUDES) -rpath @loader_path/includes/sdl $(SDL_FRAMEWORK) $(MLX_FRAMEWORK)
	@echo "\033[32m[$(NAME) is done]\033[00m"

obj/%.o: src/%.c $(HEAD)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)

re: fclean all
