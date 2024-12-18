/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:38:46 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 20:06:41 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <string.h>

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define X_RESOLUTION 1980
# define Y_RESOLUTION 1080

# define ESC 65307

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define Q_KEY 113
# define W_KEY 119
# define E_KEY 101
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define PGUP 65365
# define PGDOWN 65366

# define Z_KEY 122
# define X_KEY 120

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_coordinate
{
	double	double_y;
	double	double_x;
	double	double_z;
	int			int_y;
	int			int_x;
	int			int_z;
	int		rgb;
}		t_coordinate;

typedef struct s_grid
{
	t_coordinate *coord;
	int	y;
	int	x;
	int	scaling;
	int	y_offset;
	int	x_offset;
	float	z_scale;
}		t_grid;

typedef struct s_init
{
	void	*mlx;
	void	*win_mlx;
	t_data img;
	
}			t_init;

typedef struct s_var
{
	t_grid	grid;
	t_init	init;
}		t_var;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

int	add_shade(double distance, int trgb);
int	invert_colour(int trgb);

int	process_coords(int fd, t_grid *grid);
// int	**init_grid(int fd, int *x, int *y);

void	draw_line(t_data *img, t_coordinate point0, t_coordinate point1);

int	key_hook(int keycode, t_var *vars);

void	x_rotation(t_grid *grid, int angle);
void	y_rotation(t_grid *grid, int angle);
void	z_rotation(t_grid *grid, int angle);

#endif
