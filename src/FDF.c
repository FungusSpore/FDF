/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:54:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/15 23:15:09 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

/*int	main(int argc, char **argv)*/
int main (int argc, char **argv)
{
	int		fd;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_grid	grid;

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
	grid.grid = init_grid(fd, &grid.x, &grid.y);
	if (!grid.grid || !grid.x || !grid.y)
	{
		ft_printf("Invalid Map\n");
		return (1);
	}
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
															&img.line_length, &img.endian);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
	/*// Octant 1: (0 <= slope <= 1)*/
	/*draw_line(&img, 200, 500, 300, 550);*/
	/*// Octant 2: (slope > 1)*/
	/*draw_line(&img, 200, 500, 220, 600);*/
	/*// Octant 3: (-1 <= slope < 0)*/
	/*draw_line(&img, 200, 500, 300, 450);*/
	/*// Octant 4: (slope < -1)*/
	/*draw_line(&img, 200, 500, 220, 400);*/
	/*// Octant 5: (0 <= slope <= 1, mirrored)*/
	/*draw_line(&img, 200, 500, 100, 450);*/
	/*// Octant 6: (slope > 1, mirrored)*/
	/*draw_line(&img, 200, 500, 180, 400);*/
	/*// Octant 7: (-1 <= slope < 0, mirrored)*/
	/*draw_line(&img, 200, 500, 100, 550);*/
	/*// Octant 8: (slope < -1, mirrored)*/
	/*draw_line(&img, 200, 500, 180, 600);*/
