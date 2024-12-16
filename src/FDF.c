/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/17 00:31:57 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

t_coordinate	*isometric_projection(t_grid grid)
{
	t_coordinate *projection_coords;
	int		y;
	int		x;
	int		i;
	int		scaling;

	y = -1;
	i = 0;
	scaling = 20;
	projection_coords = malloc(sizeof(t_coordinate) * (grid.y * grid.x));
	if (!projection_coords)
		return (NULL);
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x)
		{
			projection_coords[i].x = (x * cos(120) + y * cos(120 + 2) + \
				grid.grid[y][x] * cos(120 - 2)) * scaling + X_RESOLUTION/2;
			projection_coords[i].y = (x * sin(120) + y * sin(120 + 2) + \
				grid.grid[y][x] * sin(120 - 2)) * scaling + Y_RESOLUTION/2;
			i++;
		}
	}
	return (projection_coords);
}

// memory leak
void	put_projection(t_grid grid, t_data *img, t_coordinate *projection_coords)
{
	int				i;
	int				x;
	int				y;
	int				size;

	projection_coords = isometric_projection(grid);
	size = grid.x * grid.y;
	i = 0;
	y = -1;
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x)
		{
			my_mlx_pixel_put(img, projection_coords[i].x, projection_coords[i].y, RED);
			if (x != grid.x - 1)
				draw_line(img, projection_coords[i].x, projection_coords[i].y, \
							projection_coords[i + 1].x, projection_coords[i + 1].y);
			if (y != grid.y - 1)
				draw_line(img, projection_coords[i].x, projection_coords[i].y, \
							projection_coords[i + grid.x].x, projection_coords[i + grid.x].y);
			i++;
		}
	}
}

int main (int argc, char **argv)
{
	int		fd;
	t_init init;
	t_data	img;
	t_grid	grid;
	t_coordinate	*projection_coords;

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
	init.mlx = mlx_init();
	init.win_mlx = mlx_new_window(init.mlx, X_RESOLUTION, Y_RESOLUTION, "So Long Is Cringe");
	img.img = mlx_new_image(init.mlx, X_RESOLUTION, Y_RESOLUTION);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
															&img.line_length, &img.endian);



	projection_coords = isometric_projection(grid);
	mlx_key_hook(init.win_mlx, int (*funct_ptr)(), void *param)
	put_projection(grid, &img, projection_coords);



	mlx_put_image_to_window(init.mlx, init.win_mlx, img.img, 0, 0);
	mlx_loop(init.mlx);
}
