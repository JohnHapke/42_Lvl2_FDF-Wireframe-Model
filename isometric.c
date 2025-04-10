/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:19:57 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/10 11:50:09 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_z_scale(t_map *map)
{
	int	range;

	range = abs(map->zmax - map->zmin);
	if (range <= 5)
		return (30.0);
	else if (range <= 20)
		return (10.0);
	else if (range <= 50)
		return (20.0);
	else
		return (15.0);
}

void	ft_isometric_calc(t_map *map, t_isometric *iso, int i)
{
	int		j;
	double	scale;
	double	angle;
	double	z_scale;
	double	z_value;

	scale = fmin(1700.0 / (map->xmax + map->ymax),
			1500.0 / (map->xmax + map->ymax));
	angle = 30 * MY_PI / 180;
	z_scale = ft_z_scale(map);
	z_value = ft_z_scale(map);
	if (map->zmax != map->zmin)
		z_scale = fmin(scale, z_value / (map->zmax - map->zmin));
	j = -1;
	while (++j < (map->xmax))
	{
		iso->isometric[i][j].x
			= scale *((map->points[i][j].x - map->xmax / 2)
				- (map->points[i][j].y - map->ymax / 2)) * cos(angle);
		iso->isometric[i][j].y
			= scale *((map->points[i][j].x - map->xmax / 2)
				+ (map->points[i][j].y - map->ymax / 2)) * sin(angle)
			- (map->points[i][j].z * z_scale);
		iso->isometric[i][j].z = map->points[i][j].z;
	}
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
			error_handler(NULL, 1);
		ft_isometric_calc(map, iso, i);
	}
}
