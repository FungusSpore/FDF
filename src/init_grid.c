/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:48:58 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/13 18:31:51 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	free_all(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

void	get_next_row(t_list **point, int fd)
{
	char	**nums;
	int		i;
	int		x;
	int		*row;
	char	*line;
	int		*grid;

	x = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		nums = ft_split(line, ' ');
		while (nums[i++])
			x++;
		row = malloc(sizeof(int) * x);
		if (!row)
			return ;
		i = -1;
		while (nums[++i])
			row[i] = ft_atoi(nums[i]);
		free_all(nums);
		ft_lstadd_back(point, ft_lstnew(row));
		free(line);
		line = get_next_line(fd);
	}
}

int	*init_grid(int fd)
{
	int		x;
	char	*line;
	char	**nums;

	x = 0;
	line = get_next_line(fd);
	nums = ft_split(line, ' ');

	if (x)
}

int	**get_points(char *file)
{
	int	fd;
	t_list	*points;

	points = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(strerror(fd));
		exit(1);
	}
	get_next_row(&points, fd);

	
}
