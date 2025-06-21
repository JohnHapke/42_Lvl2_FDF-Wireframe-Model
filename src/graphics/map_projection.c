/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:19:52 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:20:21 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_center_map(t_map *map, t_isometric *iso)
{
	double	border[4];
	int		i;
	int		j;

	border[0] = INFINITY;
	border[1] = INFINITY;
	border[2] = INFINITY;
	border[3] = INFINITY;
	i = -1;
	while (++i < map->ymax)
	{
		j = -1;
		while (++j < map->xmax)
		{
			if (iso->isometric[i][j].x < border[0])
				border[0] = iso->isometric[i][j].x;
			if (iso->isometric[i][j].x > border[1])
				border[1] = iso->isometric[i][j].x;
			if (iso->isometric[i][j].y < border[2])
				border[2] = iso->isometric[i][j].y;
			if (iso->isometric[i][j].y > border[3])
				border[3] = iso->isometric[i][j].y;
		}
	}
	ft_offset_map(map, iso, border);
}

void	ft_offset_map(t_map *map, t_isometric *iso, double border[4])
{
	int		i;
	int		j;
	double	offset_x;
	double	offset_y;

	i = -1;
	offset_x = (border[0] + border[1]) / 2;
	offset_y = (border[2] + border[3]) / 2;
	while (++i < map->ymax)
	{
		j = -1;
		while (++j < map->xmax)
		{
			iso->isometric[i][j].x -= offset_x;
			iso->isometric[i][j].y -= offset_y;
		}
	}
}
