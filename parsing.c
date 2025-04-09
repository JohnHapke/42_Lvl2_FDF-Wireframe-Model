/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:50:01 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/08 15:03:44 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pars_handler(char **argv, t_map *map)
{
	int		fds;

	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
		error_handler(NULL, 0);
	ft_pars_array_counter(fds, map);
	close(fds);
	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
	{
		free_map(map, NULL);
		error_handler(NULL, 0);
	}
	ft_pars_fdf_file(fds, map);
	close(fds);
	ft_find_z_range(map);
}

void	ft_pars_array_counter(int fds, t_map *map)
{
	char	*line;
	char	**value;

	map->ymax = 0;
	map->xmax = 0;
	while (1)
	{
		line = get_next_line(fds);
		if (!line)
			break ;
		value = ft_split(line, ' ');
		while (map->ymax == 0 && value[map->xmax] != NULL)
			map->xmax++;
		free(line);
		ft_free(value);
		map->ymax++;
	}
	ft_pars_mem_allocation(map);
}

void	ft_pars_mem_allocation(t_map *map)
{
	int		i;

	i = -1;
	map->points = ft_calloc(map->ymax, sizeof(t_point *));
	if (!map->points)
		error_handler(0, 0);
	while (++i < map->ymax)
	{
		map->points[i] = ft_calloc(map->xmax, sizeof(t_point));
		if (!map->points[i])
		{
			while (--i >= 0)
				free(map->points[i]);
			free(map->points);
			map->points = NULL;
			error_handler(NULL, 0);
		}
	}
}

void	ft_pars_fdf_file(int fds, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	**value;

	i = -1;
	while (++i < map->ymax)
	{
		line = get_next_line(fds);
		if (!line)
		{
			free_map(map, NULL);
			error_handler(NULL, 0);
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
