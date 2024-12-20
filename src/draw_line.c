/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:03:16 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/20 15:09:01 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static void	swap_coordinate(t_coordinate *point0, t_coordinate *point1)
{
	int	temp;

	temp = point0->int_x;
	point0->int_x = point1->int_x;
	point1->int_x = temp;
	temp = point0->int_y;
	point0->int_y = point1->int_y;
	point1->int_y = temp;
	temp = point0->rgb;
	point0->rgb = point1->rgb;
	point1->rgb = temp;
}

static void	p_adjustment(int *p, int *xy, int dir, int *params)
{
	if (*p >= 0)
	{
		*xy += dir;
		*p = *p - 2 * params[0];
	}
	*p = *p + 2 * params[1];
}

// 0 = dx 1 = dy
static void	draw_line_h(t_data *img, t_coordinate point0, t_coordinate point1)
{
	int		params[2];
	int		p;
	int		y;
	int		i;
	int		dir;

	if (point0.int_x > point1.int_x)
		swap_coordinate(&point0, &point1);
	params[0] = point1.int_x - point0.int_x;
	params[1] = point1.int_y - point0.int_y;
	dir = 1;
	if (params[1] < 0)
		dir = -1;
	params[1] *= dir;
	if (params[0] == 0)
		return ;
	y = point0.int_y;
	p = 2 * params[1] - params[0];
	i = -1;
	while (++i < params[0] + 1)
	{
		my_mlx_pixel_put(img, point0.int_x + i, y, \
		colour_gradient(point0.rgb, point1.rgb, params[0], i));
		p_adjustment(&p, &y, dir, params);
	}
}

// 0 = dy 1 = dx
static void	draw_line_v(t_data *img, t_coordinate point0, t_coordinate point1)
{
	int		params[2];
	int		p;
	int		x;
	int		i;
	int		dir;

	if (point0.int_y > point1.int_y)
		swap_coordinate(&point0, &point1);
	params[1] = point1.int_x - point0.int_x;
	params[0] = point1.int_y - point0.int_y;
	dir = 1;
	if (params[1] < 0)
		dir = -1;
	params[1] *= dir;
	if (params[0] == 0)
		return ;
	x = point0.int_x;
	p = 2 * params[1] - params[0];
	i = -1;
	while (++i < params[0] + 1)
	{
		my_mlx_pixel_put(img, x, point0.int_y + i, \
		colour_gradient(point0.rgb, point1.rgb, params[0], i));
		p_adjustment(&p, &x, dir, params);
	}
}

void	draw_line(t_data *img, t_coordinate point0, t_coordinate point1)
{
	if (abs(point1.int_x - point0.int_x) \
	> abs(point1.int_y - point0.int_y))
		draw_line_h(img, point0, point1);
	else
		draw_line_v(img, point0, point1);
}
