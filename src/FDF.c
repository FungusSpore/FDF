/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/16 14:40:27 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

t_coordinate	*isometric_projection(t_grid grid)
{
	t_coordinate *projection_coords;
	int		y;
	int		x;
	int		i;

	y = -1;
	i = 0;
	projection_coords = malloc(sizeof(t_coordinate) * (grid.y * grid.x));
	if (!projection_coords)
		return (NULL);
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x)
		{
			projection_coords[i].x = (x + 350) * (sqrt(3) * (1/sqrt(6))) \
				+ grid.grid[y][x] * (-sqrt(3) * (1/sqrt(6)));
			projection_coords[i].y = (x + 350) * (1 / sqrt(6)) + (y + 450) \
				* (2 * (1 / sqrt(6))) + grid.grid[y][x] * (1 / sqrt(6));
			i++;
		}
	}
	return (projection_coords);
}

// memory leak
void	put_projection(t_grid grid, t_data *img)
{
	t_coordinate *projection_coords;
	int				i;
	int				size;

	projection_coords = isometric_projection(grid);
	size = grid.x * grid.y;
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(img, projection_coords[i].x, projection_coords[i].y, RED);
		i++;
	}
}

int main (int argc, char **argv)
{
	int		fd;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_grid	grid;

	if (argc != 2)
	{
		ft_printf("Usage: ./FDF <map file>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s\n", strerror(fd));
		return (1);
	}
	grid.grid = init_grid(fd, &grid.x, &grid.y);
	if (!grid.grid || !grid.x || !grid.y)
	{
		ft_printf("Invalid Map\n");
		return (1);
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 900, 700, "Hello World!");
	img.img = mlx_new_image(mlx, 900, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
															&img.line_length, &img.endian);
	put_projection(grid, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
	/*// Octant 1: (0 <= slope <= 1)*/
	/*draw_line(&img, 200, 500, 300, 550);*/
	/*// Octant 2: (slope > 1)*/
	/*draw_line(&img, 200, 500, 220, 600);*/
	/*// Octant 3: (-1 <= slope < 0)*/
	/*draw_line(&img, 200, 500, 300, 450);*/
	/*// Octant 4: (slope < -1)*/
	/*draw_line(&img, 200, 500, 220, 400);*/
	/*// Octant 5: (0 <= slope <= 1, mirrored)*/
	/*draw_line(&img, 200, 500, 100, 450);*/
	/*// Octant 6: (slope > 1, mirrored)*/
	/*draw_line(&img, 200, 500, 180, 400);*/
	/*// Octant 7: (-1 <= slope < 0, mirrored)*/
	/*draw_line(&img, 200, 500, 100, 550);*/
	/*// Octant 8: (slope < -1, mirrored)*/
	/*draw_line(&img, 200, 500, 180, 600);*/
