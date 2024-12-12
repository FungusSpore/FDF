/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:52:18 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/12 21:54:55 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		x;
	int		y;

	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
															&img.line_length, &img.endian);
	// square
	// while (i++ < 500)
	// {
	// 	my_mlx_pixel_put(&img, i, 0, RED);
	// 	my_mlx_pixel_put(&img, 0, i, RED);
	// 	my_mlx_pixel_put(&img, i, 500, RED);
	// 	my_mlx_pixel_put(&img, 500, i, RED);
	// }
	// triangle
	while (y++ < 1000)	
	{
		x = 0;
		while (x++ < 100000)
			my_mlx_pixel_put(&img, y, x, x);
	}
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
