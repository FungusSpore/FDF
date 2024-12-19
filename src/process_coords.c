/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_coords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jianwong <jianwong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:13:07 by jianwong          #+#    #+#             */
/*   Updated: 2024/12/19 13:46:20 by jianwong         ###   ########.fr       */
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

int	htoi(char c)
{
	char	*hex_base;
	int		i;

	hex_base = "0123456789ABCDEF";
	i = 0;
	while (hex_base[i] && c != hex_base[i])
		i++;
	return (i);
}

// 0x810202
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
	int	i;
	char		**point;
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
		ft_lstadd_back(temp, ft_lstnew(placeholder));
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
	int	j;
	t_coordinate	*result;
	t_list	*temp2;

	j = 0;
	result = malloc(sizeof(t_coordinate) * ft_lstsize(temp));
	if (!result)
		return (NULL);
	while (temp)
	{
		result[j].double_x = ((t_coordinate *)temp->content)->double_x;
		result[j].double_y = ((t_coordinate *)temp->content)->double_y;
		result[j].double_z = ((t_coordinate *)temp->content)->double_z;
		result[j].rgb = ((t_coordinate *)temp->content)->rgb;
		temp2 = temp;	
		temp = temp->next;
		free(temp2->content);
		free(temp2);
		j++;
	}
	return (result);
}

int	process_coords(int fd, t_grid *grid)
{
	char	**points;
	char	*line;
	t_list	*temp;

	grid->y = 0;
	grid->x = 0;
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
	}
	grid->coord = covert_list_to_arr(temp);
	if (!grid->coord || !grid->y)
		return (1);
	return (0);
}

// #include <stdio.h>
//
// // Function to print the grid
// void print_grid(t_grid *grid)
// {
//     int i;
//
//     if (!grid || !grid->coord)
//     {
//         printf("Error: Grid is empty or not initialized.\n");
//         return;
//     }
//
//     printf("Grid (x, y, z, rgb):\n");
//     for (i = 0; i < grid->x * grid->y; i++)
//     {
//         printf("%d ",
//                // grid->coord[i].x);
//                // grid->coord[i].y);
//                // grid->coord[i].z);
//                // grid->coord[i].rgb);
//         if ((i + 1) % grid->x == 0)
//             printf("\n");
//     }
// }
//
// int main(int argc, char **argv)
// {
//     int fd;
//     t_grid grid;
//
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
//         return (1);
//     }
//
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//
//     // Initialize the grid and process the file
//     if (process_coords(fd, &grid))
//     {
//         fprintf(stderr, "Error processing file.\n");
//         close(fd);
//         return (1);
//     }
//
//     close(fd);
//
//     // Print the processed grid
//     print_grid(&grid);
//
//     // Free the allocated grid memory
//     free(grid.coord);
//     return (0);
// }
