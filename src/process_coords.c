/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_coords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:13:07 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/20 15:14:41 by jianwong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static void	free_all(char **nums)
{
	int	i;

	i = 0;
	while (nums[i])
		free(nums[i++]);
	free(nums);
}

static int	process_colour(char *colour)
{
	int		r;
	int		g;
	int		b;
	int		i;

	i = 2;
	r = 0;
	g = 0;
	b = 0;
	while (i < 4)
	{
		r *= 16;
		r += htoi(colour[i++]);
	}
	while (i < 6)
	{
		g *= 16;
		g += htoi(colour[i++]);
	}
	while (i < 8)
	{
		b *= 16;
		b += htoi(colour[i++]);
	}
	return (create_trgb(0, r, g, b));
}

static int	process_points(char **points, t_list **temp, t_grid *grid)
{
	int				i;
	char			**point;
	t_coordinate	*placeholder;

	i = -1;
	while (points[++i])
	{
		placeholder = malloc(sizeof(t_coordinate));
		if (!placeholder)
			return (1);
		point = ft_split(points[i], ',');
		placeholder->double_x = i;
		placeholder->double_y = grid->y;
		placeholder->double_z = atoi(point[0]);
		placeholder->rgb = RED;
		if (point[1])
			placeholder->rgb = process_colour(point[1]);
		ft_lstadd_front(temp, ft_lstnew(placeholder));
		free_all(point);
	}
	if (grid->x < 1)
		grid->x = i;
	if (grid->x != i)
		return (1);
	return (0);
}

static t_coordinate	*covert_list_to_arr(t_list *temp)
{
	int				size;
	t_list			*temp2;
	t_coordinate	*result;

	size = ft_lstsize(temp);
	result = malloc(sizeof(t_coordinate) * size--);
	if (!result)
		return (NULL);
	while (temp)
	{
		result[size].double_x = ((t_coordinate *)temp->content)->double_x;
		result[size].double_y = ((t_coordinate *)temp->content)->double_y;
		result[size].double_z = ((t_coordinate *)temp->content)->double_z;
		result[size].rgb = ((t_coordinate *)temp->content)->rgb;
		temp2 = temp;
		temp = temp->next;
		free(temp2->content);
		free(temp2);
		size--;
	}
	return (result);
}

int	process_coords(int fd, t_grid *grid)
{
	char	**points;
	char	*line;
	t_list	*temp;

	temp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		points = ft_split(line, ' ');
		if (process_points(points, &temp, grid))
		{
			free(line);
			free_all(points);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
		grid->y++;
		free_all(points);
	}
	grid->coord = covert_list_to_arr(temp);
	if (!grid->coord || !grid->y)
		return (1);
	return (0);
}
