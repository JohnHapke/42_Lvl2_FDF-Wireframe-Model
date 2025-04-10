/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:06:29 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/10 11:20:20 by jhapke           ###   ########.fr       */
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

uint32_t	fix_endianness(uint32_t color)
{
	return (((color >> 24) & 0xFF)
		| ((color >> 8) & 0xFF00)
		| ((color << 8) & 0xFF0000)
		| ((color << 24) & 0xFF000000));
}

uint32_t	ft_get_color_by_height(float z, t_map *maps)
{
	double		percentage;
	uint32_t	color;

	if (maps->zmax == maps->zmin)
		return (fix_endianness(0xFFFFFFFF));
	percentage = (double)(z - maps->zmin) / (maps->zmax - maps->zmin);
	if (percentage < 0)
		percentage = 0;
	if (percentage > 1)
		percentage = 1;
	if (percentage < 0.5)
	{
		color = (0xFF000000 | (uint32_t)(255 * percentage * 2) << 8
				| (uint32_t)(255 * (1 - percentage * 2)));
	}
	else
	{
		color = (0xFF000000 | (uint32_t)(255 * (percentage - 0.5) * 2) << 16
				| (uint32_t)(255 * (1 - (percentage - 0.5) * 2)) << 8);
	}
	return (fix_endianness(color));
}
