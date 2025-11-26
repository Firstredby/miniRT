CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MLX		= -lmlx -lX11 -lXext -lm
HEADERS = include/vector.h \
		  include/color.h \
		  include/camera.h \
		  include/lights.h \
		  include/shapes.h \
		  include/render.h \
		  include/parsing.h \
		  include/minirt.h
NAME	= miniRT
SRC		= src/main.c \
		  src/parsing/init_scene.c \
		  src/parsing/parse_ambient.c \
		  src/parsing/parse_camera.c \
		  src/parsing/parse_cylinder.c \
		  src/parsing/parse_helper.c \
		  src/parsing/parse_light.c \
		  src/parsing/parse_plane.c \
		  src/parsing/parse_scene.c \
		  src/parsing/parse_sphere.c \
		  src/parsing/validate_file.c \
		  src/parsing/validate_helper.c \
		  src/parsing/validate_scene.c \
		  src/parsing/utils/free_scene.c \
		  src/parsing/utils/ft_empty_line.c \
		  src/parsing/utils/ft_free_array.c \
		  src/parsing/utils/whitespace.c \
		  src/parsing/utils/ft_print_error.c \
		  src/execution/debug_menu.c \
		  src/execution/rendering/render.c \
		  src/execution/math_methods/math_func.c \
		  src/execution/math_methods/lights_and_colors/color_utils.c \
		  src/execution/math_methods/lights_and_colors/lights.c \
		  src/execution/math_methods/shapes_calculation/shapes_calculation.c \
		  src/execution/math_methods/vectors/vec_utils.c \
		  src/execution/math_methods/vectors/vec_utils2.c 

OBJ_DIR      = obj
OBJ_DEBUGDIR = obj_debug
OBJ          = $(SRC:.c=.o)
OBJ_DEBUG    = $(SRC:.c=.o)
LIBFT	= libft/libft.a

%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -DDEBUG -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

debug: $(OBJ_DEBUG)
	make -C libft
	$(CC) -DDEBUG $(CFLAGS) $(OBJ_DEBUG) $(LIBFT) $(MLX) -o $(NAME)

clean:
	make clean -C libft
	rm -rf $(OBJ)
	rm -rf $(OBJ_DEBUG=)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
