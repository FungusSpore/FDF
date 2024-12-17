/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/17 23:53:06 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"
#include <stdio.h>

t_coordinate	*isometric_projection(t_grid grid)
{
	t_coordinate *projection_coords;
	int		y;
	int		x;
	int		i;
	int		scaling;

	printf("here\n");
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
				grid.coord[y*x + x].z * cos(120 - 2)) * scaling + X_RESOLUTION/2;
			projection_coords[i].y = (x * sin(120) + y * sin(120 + 2) + \
				grid.coord[y*x + x].z * sin(120 - 2)) * scaling + Y_RESOLUTION/2; i++;
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

int	key_hook(int keycode, t_init *init)
{
	if (keycode == ESC)
		mlx_destroy_window(init->mlx, init->win_mlx);
	return (0);
}

int	close_win(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win_mlx);
	return (0);
}

// int	mouse_hook(int keycode, t_init *init)
// {
// 	if (keycode == MOUSE)
// 		mlx_destroy_window(init->mlx, init->win_mlx);
// 	return (0);
// }

static int	check_and_create_grid(t_grid *grid, int argc, char **argv)
{
	int		fd;
	// initial checks
	if (argc != 2)
	{
		ft_printf("Usage: ./FDF <map file>\n");
		return (1);
	}
	// read the file into a grid
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("%s\n", strerror(fd));
		return (1);
	}
	process_coords(fd, grid);
	if (!grid->grid || !grid->x || !grid->y)
	{
		ft_printf("Invalid Map\n");
		return (1);
	}
	close(fd);
	return (0);
}

int	render_next_frame(t_grid grid, t_init *init)
{
	t_coordinate	*projection_coords;

	// turn grid into projection if projection_coords is NULL
	projection_coords = isometric_projection(grid);
	put_projection(grid, &init->img, projection_coords);
	mlx_put_image_to_window(init->mlx, init->win_mlx, init->img.img, 0, 0);
	return (0);
}

int main (int argc, char **argv)
{
	t_init init;
	t_grid	grid;

	check_and_create_grid(&grid, argc, argv);
	// init the mlx window, display and img
	init.mlx = mlx_init();
	init.win_mlx = mlx_new_window(init.mlx, X_RESOLUTION, Y_RESOLUTION, "So Long Is Cringe");
	init.img.img = mlx_new_image(init.mlx, X_RESOLUTION, Y_RESOLUTION);
	init.img.addr = mlx_get_data_addr(init.img.img, &init.img.bits_per_pixel, \
															&init.img.line_length, &init.img.endian);
	mlx_loop_hook(init.mlx, render_next_frame, &init);
	mlx_hook(init.win_mlx, 17, 1, close_win, &init);
	mlx_key_hook(init.win_mlx, key_hook, &init);
	// mlx_mouse_hook(init.win_mlx, mouse_hook, &init);

	mlx_loop(init.mlx);
}


	// mlx_hook(init.win_mlx, 2, 1L<<0, close_win, &init);u mlx_hook(init.win_mlx, 7, 1L<<4, close_win, &init);
	// mlx_hook(init.win_mlx, 8, 1L<<5, close_win, &init);
