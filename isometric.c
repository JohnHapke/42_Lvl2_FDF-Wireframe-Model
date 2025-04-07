/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:19:57 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/07 11:16:57 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_center_map(t_map *map, t_isometric *iso)
{
    double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	double 	offset_x;
	double	offset_y;

	min_x = INFINITY;
	max_x = -INFINITY;
	min_y = INFINITY;
	max_y = -INFINITY;
    // Finde die Grenzen der projizierten Punkte
    for (int i = 0; i < map->ymax; i++) {
        for (int j = 0; j < map->xmax; j++) {
            if (iso->isometric[i][j].x < min_x) min_x = iso->isometric[i][j].x;
            if (iso->isometric[i][j].x > max_x) max_x = iso->isometric[i][j].x;
            if (iso->isometric[i][j].y < min_y) min_y = iso->isometric[i][j].y;
            if (iso->isometric[i][j].y > max_y) max_y = iso->isometric[i][j].y;
        }
    }
    
    // Berechne den Offset, um die Karte zu zentrieren
    offset_x = (min_x + max_x) / 2;
    offset_y = (min_y + max_y) / 2;
    
    // Wende den Offset auf alle Punkte an
    for (int i = 0; i < map->ymax; i++) {
        for (int j = 0; j < map->xmax; j++) {
            iso->isometric[i][j].x -= offset_x;
            iso->isometric[i][j].y -= offset_y;
        }
    }
}

void	ft_isometric_calc(t_map *map, t_isometric *iso, int i)
{
	int		j;
	double	scale;
	double	angle;

	scale = fmin(700.0 / (map->xmax + map->ymax),
			500.0 / (map->xmax + map->ymax));
	angle = 45 * MY_PI / 180;
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
