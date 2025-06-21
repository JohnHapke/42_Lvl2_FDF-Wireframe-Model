/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:06:29 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:20:28 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
