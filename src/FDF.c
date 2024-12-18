/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 16:19:19 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

t_coordinate	*isometric_projection(t_grid grid)
{
	t_coordinate *projection_coords;
	int		size;
	int		i;

	size = grid.x * grid.y;
	i = -1;
	projection_coords = malloc(sizeof(t_coordinate) * (grid.y * grid.x));
	if (!projection_coords)
		return (NULL);
	while (++i < size)
	{
		projection_coords[i].x = \
			(grid.coord[i].x * cos(120) + grid.coord[i].y * cos(120 + 2) + \
			grid.coord[i].z * cos(120 - 2)) * grid.scaling + grid.x_offset;
		projection_coords[i].y = \
			(grid.coord[i].x * sin(120) + grid.coord[i].y * sin(120 + 2) + \
			grid.coord[i].z * sin(120 - 2)) * grid.scaling + grid.y_offset;
		projection_coords->rgb = grid.coord[i].rgb;
	}
	return (projection_coords);
}

// memory leak
void	put_projection(t_grid grid, t_data *img, t_coordinate *projection_coords)
{
	int				i;
	int				x; int				y;
	int				size;

	size = grid.x * grid.y;
	i = 0;
	y = -1;
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x)
		{
			my_mlx_pixel_put(img, projection_coords[i].x, projection_coords[i].y, projection_coords[i].rgb);
			if (x != grid.x - 1)
				draw_line(img, projection_coords[i], projection_coords[i + 1]);
			if (y != grid.y - 1)
				draw_line(img, projection_coords[i], projection_coords[i + grid.x]);
			i++;
		}
	}
}

int	close_win(t_init *init)
{
	mlx_destroy_window(init->mlx, init->win_mlx);
	exit(1);
	return (0);
}

static int	check_and_create_grid(t_grid *grid, int argc, char **argv)
{
	int		fd;
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
	process_coords(fd, grid);
	if (!grid->coord || !grid->x || !grid->y)
	{
		ft_printf("Invalid Map\n");
		return (1);
	}
	close(fd);
	grid->scaling = 15;
	grid->x_offset = X_RESOLUTION/2;
	grid->y_offset = Y_RESOLUTION/2;
	return (0);
}

int	render_next_frame(t_var *vars)
{
	t_coordinate	*projection_coords;

	ft_bzero(vars->init.img.addr, (1980 * 1080) * (vars->init.img.bits_per_pixel/8));
	projection_coords = isometric_projection(vars->grid);
	put_projection(vars->grid, &vars->init.img, projection_coords);
	mlx_put_image_to_window(vars->init.mlx, vars->init.win_mlx, vars->init.img.img, 0, 0);
	free(projection_coords);
	return (0);
}

int main (int argc, char **argv)
{
	t_var	vars;

	check_and_create_grid(&vars.grid, argc, argv);
	vars.init.mlx = mlx_init();
	vars.init.win_mlx = mlx_new_window(vars.init.mlx, X_RESOLUTION, Y_RESOLUTION, "So Long Is Cringe");
	vars.init.img.img = mlx_new_image(vars.init.mlx, X_RESOLUTION, Y_RESOLUTION);
	vars.init.img.addr = mlx_get_data_addr(vars.init.img.img, &vars.init.img.bits_per_pixel, \
															&vars.init.img.line_length, &vars.init.img.endian);
	mlx_loop_hook(vars.init.mlx, render_next_frame, &vars);
	mlx_hook(vars.init.win_mlx, 17, 1, close_win, &vars.init);
	mlx_key_hook(vars.init.win_mlx, key_hook, &vars);
	mlx_loop(vars.init.mlx);
}
