CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MLX		= -lmlx -lX11 -lXext -lm
HEADER	= miniRT.h
NAME	= miniRT
SRC		= main.c math_func.c vec_utils.c \
		  vec_utils2.c lights.c render.c \
		  color_utils.c shapes_calculation.c \
		  debug_menu.c
OBJ_DIR      = obj
OBJ_DEBUGDIR = obj_debug
OBJ          = $(addprefix $(OBJ_DIR)/,      $(SRC:.c=.o))
OBJ_DEBUG    = $(addprefix $(OBJ_DEBUGDIR)/, $(SRC:.c=.o))
LIBFT	= libft/libft.a

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DEBUGDIR)/%.o: %.c
	mkdir -p $(OBJ_DEBUGDIR)
	$(CC) $(CFLAGS) -DDEBUG -c $< -o $@

all: $(NAME)

debug: $(OBJ_DEBUG)
	make -C libft
	$(CC) -DDEBUG $(CFLAGS) $(OBJ_DEBUG) $(LIBFT) $(MLX) -o $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DEBUGDIR)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re debug
