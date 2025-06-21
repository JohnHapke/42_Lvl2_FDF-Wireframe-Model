/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:14:37 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:40:42 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parse_array_counter(int fds, t_map *map)
{
	char	*line;
	char	**value;

	map->ymax = 0;
	map->xmax = 0;
	while (1)
	{
		line = ft_get_next_line(fds);
		if (!line)
			break ;
		value = ft_split(line, ' ');
		if (!value)
		{
			free(line);
			ft_error_handler(NULL, ERROR_PARSING);
		}
		ft_control_map(map, value);
		free(line);
		ft_free(value);
		map->ymax++;
	}
	if (map->ymax == 0 || map->xmax == 0)
		ft_error_handler(NULL, ERROR_PARSING);
	ft_parse_mem_allocation(map);
}

void	ft_parse_mem_allocation(t_map *map)
{
	int		i;

	i = -1;
	map->points = ft_calloc(map->ymax, sizeof(t_point *));
	if (!map->points)
		ft_error_handler(NULL, ERROR_MEMORY_ALLOC);
	while (++i < map->ymax)
	{
		map->points[i] = ft_calloc(map->xmax, sizeof(t_point));
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			map->points = NULL;
			ft_error_handler(NULL, ERROR_MEMORY_ALLOC);
		}
	}
}

void	ft_control_map(t_map *map, char **value)
{
	int	column_count;

	column_count = 0;
	while (value[column_count] != NULL)
		column_count++;
	if (map->ymax == 0)
		map->xmax = column_count;
	else if (column_count != map->xmax)
		ft_error_handler(NULL, ERROR_PARSING);
}
