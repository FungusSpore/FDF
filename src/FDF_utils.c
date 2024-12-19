/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:35:40 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/19 23:36:03 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	init_settings(t_grid *grid)
{
	grid->scaling = 15;
	grid->z_scale = 1;
	grid->x_offset = X_RESOLUTION/2;
	grid->y_offset = Y_RESOLUTION/2;
	grid->x_angle = 0;
	grid->y_angle = 0;
	grid->z_angle = 0;
	grid->is_parallel = 0;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > X_RESOLUTION || y < 0 || y > Y_RESOLUTION)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
