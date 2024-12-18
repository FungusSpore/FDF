/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:48:58 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/17 23:43:15 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"
#include <sys/types.h>

static void	free_all(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

static int	*convert_to_int(char **nums, int *x)
{
	int		*arr;
	int		i;

	i = 0;
	while (nums[i++]);
	arr = malloc(sizeof(int) * i);
	if (!arr)
		return (NULL);
	i = -1;
	while (nums[++i])
		arr[i] = ft_atoi(nums[i]);
	if (*x < 1)
		*x = i + 1;
	if (*x != i + 1)
	{
		free_all(nums);
		return (NULL);
	}
	free_all(nums);
	return (arr);
}

static int	**list_to_arr(t_list *row, int x)
{
	int	i;
	int	j;
	int	**result;
	int	*current_row;
	t_list	*temp;

	result = malloc(sizeof(int *) * ft_lstsize(row));
	j = 0;
	if (!result)
		return (NULL);
	while (row)
	{
		i = x;
		current_row = malloc(sizeof(int) * x);
		if (!current_row)
			return (NULL);
		while (i--)
			current_row[i] = ((int *)row->content)[i];
		result[j++]	= current_row;
		temp = row;	
		row = row->next;
		free(temp->content);
		free(temp);
	}
	return (result);
}

// x and y both set to 1 index instead of zero
void	init_grid(int fd, t_grid *grid)
{
	int		i;
	int		*arr;
	char	*line;
	char	**nums;
	char	**point_colour;
	t_coordinate *coord;
	t_list	*row;

	grid->x = 0;
	grid->y = 0;

	row = NULL;
	line = get_next_line(fd);

	while (line)
	{
		i = -1;
		nums = ft_split(line, ' ');
		while (nums[++i])
		{
			point_colour = ft_split(nums[i], ',');
			coord = malloc(sizeof(t_coordinate));
			if (!coord)
				return ;
			coord->y = grid->y;
			coord->x = i;
			coord->z = atoi(point_colour[0]);
			if (!point_colour)
				coord->rgb = BLUE; // to be continued;
			else
				coord->rgb = RED;
		}
		arr = convert_to_int(nums, &grid->x);
		if (!arr)
			return ;
		ft_lstadd_back(&row, ft_lstnew(arr));
		free(line);
		line = get_next_line(fd);
		(grid->y)++;
	}
	if (grid->y == 0)
		return ;
	return (list_to_arr(row, grid->x));
}
// int	main(int argc, char **argv)
// {
// 	int fd = open(argv[1], O_RDONLY);
// 	int x = 0;
// 	int	y = 0;
// 	int	**grid = init_grid(fd, &x, &y);
//
// 	if (!y || !x || !grid)
// 	{
// 		ft_printf("invalid map\n");
// 		return (1);
// 	}
// 	int j = 0;
// 	int i = 0;
// 	while (i < y)
// 	{
// 		j = 0;
// 		while (j < x)
// 			ft_printf("%d ", grid[i][j++]);
// 		ft_printf("\n");
// 		i++;
// 	}
// }
