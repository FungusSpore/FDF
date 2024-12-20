/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/20 17:07:03 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	close_win(t_var *vars)
{
	mlx_destroy_image(vars->init.mlx, vars->init.img.img);
	mlx_destroy_window(vars->init.mlx, vars->init.win_mlx);
	mlx_destroy_display(vars->init.mlx);
	free(vars->grid.coord);
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
	grid->y = 0;
	grid->x = 0;
	init_settings(grid);
	process_coords(fd, grid);
	if (!grid->coord || !grid->x || !grid->y)
	{
		ft_printf("Invalid Map\n");
		return (1);
	}
	close(fd);
	return (0);
}

void	z_scaling(float z_scale, t_coordinate *projection_coords, int size)
{
	int	i;

	i = 0;
	while (i < size)
		projection_coords[i++].double_z *= z_scale;
}

int	render_next_frame(t_var *vars)
{
	t_coordinate	*projection_coords;
	int				size;

	size = vars->grid.y * vars->grid.x;
	ft_bzero(vars->init.img.addr, (1980 * 1080) \
	* (vars->init.img.bits_per_pixel / 8));
	projection_coords = malloc(sizeof(t_coordinate) * size);
	if (!projection_coords)
		return (0);
	ft_memcpy(projection_coords, vars->grid.coord, \
	(vars->grid.y * vars->grid.x) * sizeof(t_coordinate));
	z_scaling(vars->grid.z_scale, projection_coords, size);
	projection_rotation(vars->grid, projection_coords);
	if (!vars->grid.is_parallel)
		isometric_projection(vars->grid, projection_coords);
	else
		parallel_projection(vars->grid, projection_coords);
	put_projection(vars->grid, &vars->init.img, projection_coords);
	mlx_put_image_to_window(vars->init.mlx, vars->init.win_mlx, \
	vars->init.img.img, 0, 0);
	free(projection_coords);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	vars;

	if (check_and_create_grid(&vars.grid, argc, argv))
		return (1);
	vars.init.mlx = mlx_init();
	vars.init.win_mlx = \
	mlx_new_window(vars.init.mlx, X_RESOLUTION, \
	Y_RESOLUTION, "So Long Is Cringe");
	vars.init.img.img = \
	mlx_new_image(vars.init.mlx, X_RESOLUTION, Y_RESOLUTION);
	vars.init.img.addr = \
	mlx_get_data_addr(vars.init.img.img, &vars.init.img.bits_per_pixel, \
	&vars.init.img.line_length, &vars.init.img.endian);
	mlx_loop_hook(vars.init.mlx, render_next_frame, &vars);
	mlx_hook(vars.init.win_mlx, 17, 1, close_win, &vars);
	mlx_key_hook(vars.init.win_mlx, key_hook, &vars);
	mlx_loop(vars.init.mlx);
}
