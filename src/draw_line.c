/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:03:16 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 23:17:40 by jianwong         ###   ########.fr       */
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

		// swap_coordinate(&point0.int_x, &point0.int_y, &point1.int_x, &point1.int_y);
static void	draw_lineH(t_data *img, t_coordinate point0, t_coordinate point1)
{
	int		dx;
	int		dy;
	int		p;
	int		y;
	int		i;
	int		dir;

	if (point0.int_x > point1.int_x)
		swap_coordinate(&point0, &point1);
	dx = point1.int_x - point0.int_x;
	dy = point1.int_y - point0.int_y;
	dir = 1;
	if (dy < 0)
		dir = -1;
	dy *= dir;
	if (dx != 0)
	{
		y = point0.int_y;
		p = 2 * dy - dx;
		i = -1;
		while (++i < dx + 1)
		{
			my_mlx_pixel_put(img ,point0.int_x + i, y, colour_gradient(point0.rgb, point1.rgb, dx, i));
			if (p >= 0)
			{
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;
		}
	}
}

static void	draw_lineV(t_data *img, t_coordinate point0, t_coordinate point1)
{
	int		dx;
	int		dy;
	int		p;
	int		x;
	int		i;
	int		dir;

	if (point0.int_y > point1.int_y)
		swap_coordinate(&point0, &point1);
	dx = point1.int_x - point0.int_x;
	dy = point1.int_y - point0.int_y;
	dir = 1;
	if (dx < 0)
		dir = -1;
	dx *= dir;
	if (dy != 0)
	{
		x = point0.int_x;
		p = 2 * dx - dy;
		i = -1;
		while (++i < dy + 1)
	{
			my_mlx_pixel_put(img , x, point0.int_y + i, colour_gradient(point0.rgb, point1.rgb, dy, i));
			if (p >= 0)
			{
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;
		}
	}
}

void	draw_line(t_data *img, t_coordinate point0, t_coordinate point1)
{
	if (abs(point1.int_x -point0.int_x) > abs(point1.int_y - point0.int_y))
		draw_lineH(img, point0, point1);
	else
		draw_lineV(img, point0, point1);
}

// void	draw_line(t_data *img, int x0, int y0, int x1, int y1)
// {
// 	if (abs(x1 - x0) > abs(y1 - y0))
// 		draw_lineH(img, x0, y0, x1, y1);
// 	else
// 		draw_lineV(img, x0, y0, x1, y1);
// }
/*int	main(void)*/
/*{*/
/*	int		fd;*/
/*	void	*mlx;*/
/*	void	*mlx_win;*/
/*	t_data	img;*/
/*	t_grid	grid;*/
/**/
/*	mlx = mlx_init();*/
/*	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");*/
/*	img.img = mlx_new_image(mlx, 1920, 1080);*/
/*	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \*/
/*															&img.line_length, &img.endian);*/
/*	draw_line(&img, 6, 7, 15, 30);*/
/*	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);*/
/*	mlx_loop(mlx);*/
/*}*/
