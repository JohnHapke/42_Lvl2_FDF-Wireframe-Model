/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:42:49 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/07 10:43:26 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return ;
	while (ar[i])
		free(ar[i++]);
	free(ar);
}

void	free_map(t_map	*map, t_isometric *iso)
{
	int	i;

	if (iso && map)
	{
		i = -1;
		while (++i < map->ymax)
			free(iso->isometric[i]);
		free(iso->isometric);
		free(iso);
	}
	i = -1;
	if (map)
	{
		while (++i < map->ymax)
			free(map->points[i]);
		free(map->points);
		free(map);
	}
}

void	free_wires(t_map *map, t_line_data **lines)
{
	int	i;
	int	lines_count;

	lines_count = (map->xmax - 1) * (map->ymax)
		+ (map->xmax) * (map->ymax - 1);
	if (lines)
	{
		i = -1;
		while (++i < lines_count)
		{
			free(lines[i]->line);
			free(lines[i]);
		}
		free(lines);
	}
}

void	ft_lines_free(t_line_data **lines, int line_count)
{
	int	i;

	i = -1;
	if (!lines)
		return ;
	while (++i < line_count)
	{
		if (lines[i])
		{
			if (lines[i]->line)
				free(lines[i]->line);
			free(lines[i]);
		}
	}
	free(lines);
}
