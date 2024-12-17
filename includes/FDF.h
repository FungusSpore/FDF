/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:38:46 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/17 23:44:00 by jianwong         ###   ########.fr       */
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
# define X_BUTTON 939966976

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
	int	y;
	int	x;
	int	z;
	int	rgb;
}		t_coordinate;

typedef struct s_grid
{
	int	**grid;
	t_coordinate *coord;
	int	y;
	int	x;
}		t_grid;

typedef struct s_init
{
	void	*mlx;
	void	*win_mlx;
	t_data img;
	
}			t_init;

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

void	draw_line(t_data *img, int x0, int y0, int x1, int y1);

#endif
