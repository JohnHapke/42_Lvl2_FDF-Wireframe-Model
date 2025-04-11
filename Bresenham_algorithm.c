/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bresenham_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:11:51 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/11 10:12:08 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_algorithm_xcalc(t_line_data *data)
{
	int	er;
	int	i;

	i = -1;
	data->x_step = -1;
	if (data->dx >= 0)
		data->x_step = 1;
	data->y_step = -1;
	if (data->dy >= 0)
		data->y_step = 1;
	er = 2 * abs(data->dx) - abs(data->dy);
	while (++i < abs((data->dx)))
	{
		er -= 2 * abs(data->dy);
		data->line[i + 1].x = data->line[i].x + data->x_step;
		data->line[i + 1].z = data->line[0].z + ((double)(i + 1) / abs
				(data->dx)) * (data->line[abs(data->dx)].z - data->line[0].z);
		if (er < 0)
		{
			data->line[i + 1].y = data->line[i].y + data->y_step;
			er += 2 * abs(data->dx);
		}
		else
			data->line[i + 1].y = data->line[i].y;
	}
}

void	ft_algorithm_ycalc(t_line_data *data)
{
	int	er;
	int	i;

	i = -1;
	data->x_step = -1;
	if (data->dx >= 0)
		data->x_step = 1;
	data->y_step = -1;
	if (data->dy >= 0)
		data->y_step = 1;
	er = 2 * abs(data->dx) - abs(data->dy);
	while (++i < abs(data->dy))
	{
		er -= 2 * abs(data->dx);
		data->line[i + 1].y = data->line[i].y + data->y_step;
		data->line[i + 1].z = data->line[0].z + ((double)(i + 1) / abs
				(data->dy)) * (data->line[abs(data->dy)].z - data->line[0].z);
		if (er < 0)
		{
			data->line[i + 1].x = data->line[i].x + data->x_step;
			er += 2 * abs(data->dx);
		}
		else
			data->line[i + 1].x = data->line[i].x;
	}
}
