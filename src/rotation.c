/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:25:20 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/20 15:18:37 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static double	to_radians(int angle)
{
	return (angle * M_PI / 180.0);
}

// x = 0, y = 1, z = 2
void	com_calc(t_coordinate *coords, double *center_of_mass, int size)
{
	int		i;

	i = -1;
	center_of_mass[0] = 0;
	center_of_mass[1] = 0;
	center_of_mass[2] = 0;
	while (++i < size)
	{
		center_of_mass[0] += coords[i].double_x;
		center_of_mass[1] += coords[i].double_y;
		center_of_mass[2] += coords[i].double_z;
	}
	center_of_mass[0] /= size;
	center_of_mass[1] /= size;
	center_of_mass[2] /= size;
}

void	x_rotation(t_coordinate *projection_coords, int angle, int size)
{
	int			i;
	double		temp_y;
	double		temp_z;
	double		center_of_mass[3];

	com_calc(projection_coords, center_of_mass, size);
	i = -1;
	while (++i < size)
	{
		temp_y = \
		(projection_coords[i].double_y - center_of_mass[1]) \
		* cos(to_radians(angle)) - (projection_coords[i].double_z \
		- center_of_mass[2]) * sin(to_radians(angle));
		temp_z = \
		(projection_coords[i].double_y - center_of_mass[1]) \
		* sin(to_radians(angle)) + (projection_coords[i].double_z \
		- center_of_mass[2]) * cos(to_radians(angle));
		projection_coords[i].double_y = temp_y + center_of_mass[1];
		projection_coords[i].double_z = temp_z + center_of_mass[2];
	}
}

void	y_rotation(t_coordinate *projection_coords, int angle, int size)
{
	int			i;
	double		temp_x;
	double		temp_z;
	double		center_of_mass[3];

	com_calc(projection_coords, center_of_mass, size);
	i = -1;
	while (++i < size)
	{
		temp_x = \
		(projection_coords[i].double_z - center_of_mass[2]) \
		* sin(to_radians(angle)) + (projection_coords[i].double_x \
		- center_of_mass[0]) * cos(to_radians(angle));
		temp_z = \
		(projection_coords[i].double_z - center_of_mass[2]) \
		* cos(to_radians(angle)) - (projection_coords[i].double_x \
		- center_of_mass[0]) * sin(to_radians(angle));
		projection_coords[i].double_x = temp_x + center_of_mass[0];
		projection_coords[i].double_z = temp_z + center_of_mass[2];
	}
}

void	z_rotation(t_coordinate *projection_coords, int angle, int size)
{
	int			i;
	double		temp_y;
	double		temp_x;
	double		center_of_mass[3];

	com_calc(projection_coords, center_of_mass, size);
	i = -1;
	while (++i < size)
	{
		temp_y = \
		(projection_coords[i].double_x - center_of_mass[0]) \
		* sin(to_radians(angle)) + (projection_coords[i].double_y \
		- center_of_mass[1]) * cos(to_radians(angle));
		temp_x = \
		(projection_coords[i].double_x - center_of_mass[0]) \
		* cos(to_radians(angle)) - (projection_coords[i].double_y \
		- center_of_mass[1]) * sin(to_radians(angle));
		projection_coords[i].double_y = temp_y + center_of_mass[1];
		projection_coords[i].double_x = temp_x + center_of_mass[0];
	}
}
