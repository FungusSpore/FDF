/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:03:16 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 16:13:29 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static void	swap_coordinate(int *x0, int *y0, int *x1, int *y1)
{
	int	temp;

	temp = *x0;
	*x0 = *x1;
	*x1 = temp;
	temp = *y0;
	*y0 = *y1;
	*y1 = temp;
}

static void	draw_lineH(t_data *img, t_coordinate point0, t_coordinate point1)
{
	int		dx;
	int		dy;
	int		p;
	int		y;
	int		i;
	int		dir;

	if (point0.x > point1.x)
		swap_coordinate(&point0.x, &point0.y, &point1.x, &point1.y);
	dx = point1.x - point0.x;
	dy = point1.y - point0.y;
	dir = 1;
	if (dy < 0)
		dir = -1;
	dy *= dir;
	if (dx != 0)
	{
		y = point0.y;
		p = 2 * dy - dx;
		i = -1;
		while (++i < dx + 1)
		{
			my_mlx_pixel_put(img ,point0.x + i, y, RED);
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

	if (point0.y > point1.y)
		swap_coordinate(&point0.x, &point0.y, &point1.x, &point1.y);
	dx = point1.x - point0.x;
	dy = point1.y - point0.y;
	dir = 1;
	if (dx < 0)
		dir = -1;
	dx *= dir;
	if (dy != 0)
	{
		x = point0.x;
		p = 2 * dx - dy;
		i = -1;
		while (++i < dy + 1)
	{
			my_mlx_pixel_put(img , x, point0.y + i, RED);
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
	if (abs(point1.x -point0.x) > abs(point1.y - point0.y))
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
