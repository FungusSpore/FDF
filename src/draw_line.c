/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:03:16 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/14 01:54:55 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	draw_line(int x0, int y0, int x1, int y1)
{
	float	dx;
	float	dy;
	double m;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx != 0)
	{
		m = dy / dx;
		y = y0;	
		while (i < dx + 1)
		{
			my_mlx_pixel_put(t_data *data, i, y, RED)
			p = 2*dy*i - 2*y*dx;
			pInitial = 2*dy - dx;
			if (p >= 0)
				y++;
		}

	}
}
