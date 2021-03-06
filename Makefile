# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thorker <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 20:57:04 by thorker           #+#    #+#              #
#    Updated: 2020/06/28 18:16:47 by thorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
HEADERS = includes/scop.h includes/scop_error.h
INC =  -I ~/.brew/Cellar/glfw/3.3.2/include/ -I $(LIB_DIR)/includes -I ./includes -I ~/.brew/Cellar/glew/2.1.0_1/include/ \
	   -I SDL2_image.framework/Versions/A/Headers -I ~/.brew/Cellar/sdl2/2.0.10/include
SRC = ft_delete_object.c get_shader_code.c ft_realloc.c add_smth.c create_object.c update_matrix.c hooks.c create_program.c create_vao_vbo.c main.c create_struct.c ft_loop.c ft_clear.c init_window.c ft_error.c
LIB = -L $(LIB_DIR)/ -lft -L ~/.brew/Cellar/glfw/3.3.2/lib/ -lglfw -L ~/.brew/Cellar/glew/2.1.0_1/lib/ -lGLEW \
	  -L ~/.brew/Cellar/sdl2_image/2.0.5/lib/ -lSDL2_image
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
FRWR = -framework OpenGL

SRC_DIR = src
OBJ_DIR = object
LIB_DIR	= libft
FRWR = -framework OpenGL
FLAG = -g -Wall -Wextra -Werror

.PHONY : all clean fclean lib_ft re test

$(NAME): $(OBJ_DIR) $(OBJ) 
		@make lib_ft
		$(CC) $(FLAG) $(OBJ) $(INC) $(LIB) $(FRWR) -o $(NAME)
		@echo "\033[32m"ready

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
		$(CC) $(FLAG) $(INC) -c $< -o $@

lib_ft:
		@make -C $(LIB_DIR)/

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
		@make -C $(LIB_DIR)/ clean
		@rm -rf $(OBJ_DIR)
		@echo "\033[32m"Clear
		
fclean: clean
		@rm -f $(OBJ)
		@make -C $(LIB_DIR)/ fclean
		@rm -f $(NAME)
		@echo "\033[32m"All Clear

re: fclean all
