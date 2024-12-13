NAME=FDF
SOURCE= src/FDF.c src/trgb.c src/colour_functions.c
OBJ=$(SOURCE:.c=.o)
MLX=minilibx-linux
FLAGS= -Wall -Wextra -Werror
CC= cc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(MLX) -lmlx_Linux -L/usr/lib -I$(MLX) -lXext -lX11 -lm -lz -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -I/usr/include -I$(MLX) -O3 -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f FDF

re: fclean all
