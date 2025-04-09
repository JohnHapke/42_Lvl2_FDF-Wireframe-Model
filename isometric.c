/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:19:57 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/09 08:36:20 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isometric_calc(t_map *map, t_isometric *iso, int i)
{
	int		j;
	double	scale;
	double	angle;

	scale = fmin(700.0 / (map->xmax + map->ymax),
			500.0 / (map->xmax + map->ymax));
	angle = 30 * MY_PI / 180;
	j = -1;
	while (++j < (map->xmax))
	{
		iso->isometric[i][j].x
			= scale *((map->points[i][j].x - map->xmax / 2)
				- (map->points[i][j].y - map->ymax / 2)) * cos(angle);
		iso->isometric[i][j].y
			= scale *((map->points[i][j].x - map->xmax / 2)
				+ (map->points[i][j].y - map->ymax / 2)) * sin(angle)
			- map->points[i][j].z;
		iso->isometric[i][j].z = map->points[i][j].z;
	}
}

void	free_isometric_array(t_isometric *iso, int i)
{
	while (--i >= 0)
		free(iso->isometric[i]);
	free(iso->isometric);
	iso->isometric = NULL;
}

void	ft_to_isometric(t_map *map, t_isometric *iso)
{
	int		i;

	i = -1;
	iso->isometric = ft_calloc(map->ymax, sizeof(t_point *));
	if (!iso->isometric)
		error_handler(NULL, 1);
	while (++i < (map)->ymax)
	{
		iso->isometric[i] = malloc(map->xmax * sizeof(t_point));
		if (!(iso->isometric[i]))
		{
			free_isometric_array(iso, i);
			free_map(map, iso);
			error_handler(NULL, 1);
			return ;
		}
		ft_isometric_calc(map, iso, i);
	}
}
