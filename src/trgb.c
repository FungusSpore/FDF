/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:54:46 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/13 13:39:11 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb >> 24 & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
//
// int	main(void)
// {
// 	int	trgb;
//
// 	trgb = create_trgb(255, 255, 24, 1);
// 	printf("%d\n", get_t(trgb));
// 	printf("%d\n", get_r(trgb));
// 	printf("%d\n", get_g(trgb));
// 	printf("%d\n", get_b(trgb));
// }
