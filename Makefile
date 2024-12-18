NAME=FDF
DIR_LIBFT=libft
LIBFT=$(DIR_LIBFT)/libft.a
SOURCE= src/FDF.c src/trgb.c src/colour_functions.c src/draw_utils.c src/draw_line.c src/process_coords.c src/key_hook.c src/rotation.c
OBJ=$(SOURCE:.c=.o)
MLX=minilibx-linux
FLAGS= -Wall -Wextra -Werror
CC= cc

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ -L$(MLX) -lmlx_Linux -L/usr/lib -I$(MLX) -I$(DIR_LIBFT) -lXext -lX11 -lm -lz -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -I/usr/include -I$(MLX) -I$(DIR_LIBFT) -O3 -c $< -o $@

$(LIBFT):
	make -C $(DIR_LIBFT) bonus

clean:
	rm -f src/*.o
	make -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all
