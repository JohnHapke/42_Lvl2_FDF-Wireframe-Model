/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:48:30 by jhapke            #+#    #+#             */
/*   Updated: 2025/03/27 08:56:08 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_input_handler(char **argv, t_map *map)
{
	int		fds;
	int		i;

	i = 0;
	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
		exit(1);
	ft_array_counter(fds, map);
	close(fds);
	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
		exit(1);
	ft_parse_fdf_file(fds, map);
	close(fds);
}

void	ft_array_counter(int fds, t_map *map)
{
	int		i;
	char	*line;
	char	**value;

	i = 0;
	map->ymax = 0;
	map->xmax = 0;
	while (1)
	{
		line = ft_get_next_line(fds);
		if (!line)
			break ;
		value = ft_split(line, " ");
		while (map->ymax == 0 && value[map->xmax] != NULL)
			map->xmax++;
		free(line);
		ft_free(value);
		map->ymax++;
	}
	ft_mem_allocation(map);
	free(line);
}

void	ft_mem_allocation(t_map *map)
{
	int		i;

	i = 0;
	map->points = malloc(map->ymax * sizeof(t_point *));
	if (!map->points)
		return ;
	while (i < map->ymax)
	{
		map->points[i] = malloc(map->xmax * sizeof(t_point));
		if (map->points[i] == '\0')
			return ;
		i++;
	}
}

void	ft_free(char **ar)
{
	while (*ar)
		free(*ar++);
	free(ar);
}

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
			return ;
		value = ft_split(line, " ");
		j = 0;
		while (j < map->xmax)
		{
			map->points[i][j].x = j;
			map->points[i][j].y = i;
			map->points[i][j].z = ft_atoi(value[j++]);
		}
		free(line);
		ft_free(value);
	}
}
