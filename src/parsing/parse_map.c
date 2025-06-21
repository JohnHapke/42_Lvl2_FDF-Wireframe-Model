/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:16:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:41:05 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parse_fdf_file(int fds, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	**value;

	i = -1;
	while (++i < map->ymax)
	{
		line = ft_get_next_line(fds);
		if (!line)
		{
			ft_free_map(map, NULL);
			ft_error_handler(NULL, ERROR_PARSING);
		}
		value = ft_split(line, ' ');
		j = -1;
		while (++j < map->xmax)
		{
			map->points[i][j].x = j;
			map->points[i][j].y = i;
			map->points[i][j].z = ft_atoi(value[j]);
		}
		free(line);
		ft_free(value);
	}
}

void	ft_find_z_range(t_map *maps)
{
	int	i;
	int	j;

	maps->zmax = INT32_MIN;
	maps->zmin = INT32_MAX;
	i = -1;
	while (++i < maps->ymax)
	{
		j = -1;
		while (++j < maps->xmax)
		{
			if (maps->points[i][j].z < maps->zmin)
				maps->zmin = maps->points[i][j].z;
			if (maps->points[i][j].z > maps->zmax)
				maps->zmax = maps->points[i][j].z;
		}
	}
}
