/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:16:27 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:17 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	projection_rotation(t_grid grid, t_coordinate *projection_coords)
{
	int				size;

	size = grid.y * grid.x;
	x_rotation(projection_coords, grid.x_angle, size);
	y_rotation(projection_coords, grid.y_angle, size);
	z_rotation(projection_coords, grid.z_angle, size);
}

t_coordinate	*isometric_projection(t_grid grid, t_coordinate *coords)
{
	int		size;
	int		i;

	size = grid.x * grid.y;
	i = -1;
	while (++i < size)
	{
		coords[i].int_x = \
			(coords[i].double_x * cos(120) + \
			coords[i].double_y * cos(120 + 2) + \
			coords[i].double_z * cos(120 - 2)) * \
			grid.scaling + grid.x_offset;
		coords[i].int_y = \
			(coords[i].double_x * sin(120) + \
			coords[i].double_y * sin(120 + 2) + \
			coords[i].double_z * sin(120 - 2)) * \
			grid.scaling + grid.y_offset;
	}
	return (coords);
}

void	parallel_projection(t_grid grid, t_coordinate *projection_coords)
{
	int	i;
	int	size;

	i = 0;
	size = grid.x * grid.y;
	while (i < size)
	{
		projection_coords[i].int_x = \
			projection_coords[i].double_x * grid.scaling + grid.x_offset;
		projection_coords[i].int_y = \
			projection_coords[i].double_y * grid.scaling + grid.y_offset;
		i++;
	}
}

void	put_projection(t_grid grid, t_data *img, t_coordinate *coords)
{
	int				i;
	int				x;
	int				y;
	int				size;

	size = grid.x * grid.y;
	i = 0;
	y = -1;
	while (++y < grid.y)
	{
		x = -1;
		while (++x < grid.x)
		{
			my_mlx_pixel_put(img, coords[i].int_x, \
			coords[i].int_y, coords[i].rgb);
			if (x != grid.x - 1)
				draw_line(img, coords[i], coords[i + 1]);
			if (y != grid.y - 1)
				draw_line(img, coords[i], coords[i + grid.x]);
			i++;
		}
	}
}
