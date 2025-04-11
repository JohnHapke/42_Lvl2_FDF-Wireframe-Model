/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_algorithm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:34:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/11 10:13:58 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_algorithm_row(t_line_data **data, t_isometric *iso, int i, int j)
{
	*data = malloc(sizeof(t_line_data));
	if (!*data)
		error_handler(NULL, ERROR_MEMORY_ALLOC);
	(*data)->dy = (int)round(iso->isometric[i][j + 1].y
			- iso->isometric[i][j].y);
	(*data)->dx = (int)round(iso->isometric[i][j + 1].x
			- iso->isometric[i][j].x);
	(*data)->size = abs((*data)->dy);
	if (abs((*data)->dx) > (*data)->size)
		(*data)->size = abs((*data)->dx);
	(*data)->line = malloc(((*data)->size + 1) * sizeof(t_point));
	if (!(*data)->line)
		error_handler(NULL, ERROR_MEMORY_ALLOC);
	(*data)->line[0].x = (int)round(iso->isometric[i][j].x);
	(*data)->line[0].y = (int)round(iso->isometric[i][j].y);
	(*data)->line[0].z = iso->isometric[i][j].z;
	(*data)->line[(*data)->size].z = iso->isometric[i][j + 1].z;
	if (abs((*data)->dx) > abs((*data)->dy))
		ft_algorithm_xcalc((*data));
	else
		ft_algorithm_ycalc((*data));
}

void	ft_algorithm_col(t_line_data **data, t_isometric *iso, int i, int j)
{
	*data = malloc(sizeof(t_line_data));
	if (!(*data))
		error_handler(NULL, ERROR_MEMORY_ALLOC);
	(*data)->dy = (int)round(iso->isometric[i + 1][j].y
			- iso->isometric[i][j].y);
	(*data)->dx = (int)round(iso->isometric[i + 1][j].x
			- iso->isometric[i][j].x);
	(*data)->size = abs((*data)->dy);
	if (abs((*data)->dx) > (*data)->size)
		(*data)->size = abs((*data)->dx);
	(*data)->line = malloc(((*data)->size + 1) * sizeof(t_point));
	if (!((*data)->line))
		error_handler(NULL, ERROR_MEMORY_ALLOC);
	(*data)->line[0].y = (int)round(iso->isometric[i][j].y);
	(*data)->line[0].x = (int)round(iso->isometric[i][j].x);
	(*data)->line[0].z = iso->isometric[i][j].z;
	(*data)->line[(*data)->size].z = iso->isometric[i + 1][j].z;
	if (abs((*data)->dx) > abs((*data)->dy))
		ft_algorithm_xcalc((*data));
	else
		ft_algorithm_ycalc((*data));
}

t_line_data	**ft_algorithm_handler(t_map *map, t_isometric *iso)
{
	t_line_data	**lines;
	int			i;
	int			line_count;

	line_count = (map->xmax - 1) * (map->ymax) + (map->xmax) * (map->ymax - 1);
	lines = ft_calloc(line_count, sizeof(t_line_data *));
	if (!lines)
		error_handler(NULL, ERROR_MEMORY_ALLOC);
	i = -1;
	while (++i < line_count)
		lines[i] = NULL;
	if (!ft_algorithm_m(map, iso, lines, 0))
		error_handler(NULL, ERROR_BRESENHAM);
	return (lines);
}

t_line_data	**ft_algorithm_m(t_map *map, t_isometric *iso,
			t_line_data **lines, int line_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->ymax)
	{
		j = -1;
		while (++j < map->xmax)
		{
			if (j < map->xmax - 1)
			{
				ft_algorithm_row(&lines[line_count], iso, i, j);
				if (!lines[line_count++])
					error_handler(NULL, ERROR_BRESENHAM);
			}
			if (i < map->ymax - 1)
			{
				ft_algorithm_col(&lines[line_count], iso, i, j);
				if (!lines[line_count++])
					error_handler(NULL, ERROR_BRESENHAM);
			}
		}
	}
	return (lines);
}
