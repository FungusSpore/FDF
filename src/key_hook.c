/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:28:02 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 20:27:56 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static int	key_hook_2(int keycode, t_var *vars)
{
	if (keycode == S_KEY)
		x_rotation(&vars->grid, -3);
	if (keycode == Q_KEY)
		z_rotation(&vars->grid, 3);
	if (keycode == E_KEY)
		z_rotation(&vars->grid, -3);
	if (keycode == Z_KEY)
		vars->grid.z_scale += 0.2;
	if (keycode == X_KEY)
		vars->grid.z_scale -= 0.2;
	return (0);
}

int	key_hook(int keycode, t_var *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->init.mlx, vars->init.win_mlx);
		exit(1);
	}
	if (keycode == PGUP)
		vars->grid.scaling++;
	else if (keycode == PGDOWN)
		vars->grid.scaling--;
	else if (keycode == UP)
		vars->grid.y_offset -= 10;
	else if (keycode == DOWN)
		vars->grid.y_offset += 10;
	else if (keycode == LEFT)
		vars->grid.x_offset -= 10;
	else if (keycode == RIGHT)
		vars->grid.x_offset += 10;
	else if (keycode == A_KEY)
		y_rotation(&vars->grid, 3);
	if (keycode == D_KEY)
		y_rotation(&vars->grid, -3);
	if (keycode == W_KEY)
		x_rotation(&vars->grid, 3);
	key_hook_2(keycode, vars);
	return (0);
}

