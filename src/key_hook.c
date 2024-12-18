/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:28:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 16:23:59 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"


int	key_hook(int keycode, t_var *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->init.mlx, vars->init.win_mlx);
		exit(1);
	}
	if (keycode == PGUP)
		vars->grid.scaling++;
	if (keycode == PGDOWN)
		vars->grid.scaling--;
	if (keycode == UP)
		vars->grid.y_offset -= 5;
	if (keycode == DOWN)
		vars->grid.y_offset += 5;
	if (keycode == LEFT)
		vars->grid.x_offset -= 5;
	if (keycode == RIGHT)
		vars->grid.x_offset += 5;
	return (0);
}

