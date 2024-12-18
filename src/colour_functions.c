/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:01:06 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/18 22:45:56 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"
#include <stdlib.h>

int	add_shade(double distance, int trgb)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(trgb) * distance;
	r = get_r(trgb) * distance;
	g = get_g(trgb) * distance;
	b = get_b(trgb) * distance;
	return (create_trgb(t, r, g, b));
}

int	invert_colour(int trgb)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = abs(get_t(trgb) - 255);
	r = abs(get_r(trgb) - 255);
	g = abs(get_g(trgb) - 255);
	b = abs(get_b(trgb) - 255);
	return (create_trgb(t, r, g, b));
}

int	colour_gradient(int trgb1, int trgb2, int lenght, int current)
{
	int	r;
	int	g;
	int b;
	float mix;

	mix = (float)current / (float)lenght;
	r = get_r(trgb1) * (1 - mix) + get_r(trgb2) * mix;
	g = get_g(trgb1) * (1 - mix) + get_g(trgb2) * mix;
	b = get_b(trgb1) * (1 - mix) + get_b(trgb2) * mix;
	return (create_trgb(0, r, g, b));
}
