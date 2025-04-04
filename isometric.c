/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:19:57 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/04 11:11:46 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isometric_calc(t_map *map, t_isometric *iso, double angle, int i)
{
	int	j;

	j = -1;
	while (++j < (map->xmax))
	{
		iso->isometric[i][j].x
			= (map->points[i][j].x
				- map->points[i][j].y) * cos(angle);
		iso->isometric[i][j].y
			= (map->points[i][j].x + map->points[i][j].y)
			* sin(angle) - map->points[i][j].z;
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
	double		angle;
	int			i;

	angle = 30 * MY_PI / 180;
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
		ft_isometric_calc(map, iso, angle, i);
	}
}
