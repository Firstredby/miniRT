CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
MLX		= -lmlx -lX11 -lXext -lm
HEADER	= miniRT.h
NAME	= miniRT
SRC		= main.c math_func.c vec_utils.c \
		  lights.c render.c color_utils.c \
		  shapes_calculation.c
OBJ		= $(SRC:.c=.o)
LIBFT	= libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
