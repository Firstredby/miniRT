CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MLX		= -lmlx -lX11 -lXext -lm
HEADERS = vector.h \
		  color.h \
		  camera.h \
		  lights.h \
		  shapes.h \
		  render.h \
		  parsing.h \
		  minirt.h
NAME	= miniRT
SRC		= main.c \
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
		  src/utils/free_scene.c \
		  src/utils/ft_empty_line.c \
		  src/utils/ft_free_array.c \
		  src/utils/ft_is_whitespace.c \
		  src/utils/ft_print_error.c \
		  src/debug_menu.c \
		  src/rendering/render.c \
		  src/math_methods/math_func.c \
		  src/math_methods/lights_and_colors/color_utils.c \
		  src/math_methods/lights_and_colors/lights.c \
		  src/math_methods/shapes_calculation.c \
		  src/math_methods/vec_utils.c \
		  src/math_methods/vec_utils2.c 

OBJ_DIR      = obj
OBJ_DEBUGDIR = obj_debug
OBJ          = $(addprefix $(OBJ_DIR)/,      $(SRC:.c=.o))
OBJ_DEBUG    = $(addprefix $(OBJ_DEBUGDIR)/, $(SRC:.c=.o))
LIBFT	= libft/libft.a

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DEBUGDIR)/%.o: %.c $(HEADERS)
	mkdir -p $(OBJ_DEBUGDIR)
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
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DEBUGDIR)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
