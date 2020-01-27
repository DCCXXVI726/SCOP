# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deladia <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 20:57:04 by thorker           #+#    #+#              #
#    Updated: 2020/01/24 02:53:26 by thorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
HEADERS = includes/scop.h
INC =  -I ~/.brew/Cellar/glfw/3.3/include/ -I $(LIB_DIR) -I ./includes -I ~/.brew/Cellar/glew/2.1.0/include/
SRC = kekw.c
LIB = -L $(LIB_DIR)/ -lft -L ~/.brew/Cellar/glfw/3.3/lib/ -lglfw -L ~/.brew/Cellar/glew/2.1.0/lib/ -lGLEW
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
FRWR = -framework OpenGL

SRC_DIR = src
OBJ_DIR = object
LIB_DIR	= libft
FRWR = -framework OpenGL
FLAG = -Wall -Wextra -Werror -g

.PHONY : all clean fclean lib_ft re test

$(NAME): $(OBJ_DIR) $(OBJ) 
		@make lib_ft
		$(CC) $(FLAG) $(OBJ) $(INC) $(LIB) $(FRWR) -o $(NAME)
		@echo "\033[32m"ready

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
