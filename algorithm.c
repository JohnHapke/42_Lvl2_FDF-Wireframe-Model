/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:34:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/03/28 11:15:29 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_algorithm_xcalc(t_line_data *data)
{
	float	er;
	int		i;

	i = -1;
	data->x_step = -1;
	if (data->dx >= 0)
		data->x_step = 1;
	data->y_step = -1;
	if (data->dy >= 0)
		data->y_step = 1;
	er = abs(data->dx) / 2;
	while (++i < abs(data->dx))
	{
		er -= abs(data->dy);
		data->line[i + 1].x = data->line[i].x + data->x_step;
		if (er < 0)
		{
			data->line[i + 1].y = data->line[i].y + data->y_step;
			er += abs(data->dx);
		}
		else
			data->line[i + 1].y = data->line[i].y;
	}
}

void	ft_algorithm_ycalc(t_line_data *data)
{
	float	er;
	int		i;

	i = -1;
	data->x_step = -1;
	if (data->dx >= 0)
		data->x_step = 1;
	data->y_step = -1;
	if (data->dy >= 0)
		data->y_step = 1;
	er = abs(data->dy) / 2;
	while (++i < abs(data->dy))
	{
		er -= abs(data->dx);
		data->line[i + 1].y = data->line[i].y + data->y_step;
		if (er < 0)
		{
			data->line[i + 1].x = data->line[i].x + data->x_step;
			er += abs(data->dy);
		}
		else
			data->line[i + 1].x = data->line[i].x;
	}
}

void	ft_algorithm_handler(int xmax, int ymax, int x, int y)
{
	t_line_data	*data;
	int			size;

	data = malloc(sizeof(t_line_data));
	if (!data)
		return ;
	data->dy = ymax - y;
	data->dx = xmax - x;
	size = data->dy;
	if (abs(data->dx) > abs(data->dy))
		size = data->dx;
	data->line = malloc((abs(size) + 1) * sizeof(t_point));
	if (!data->line)
	{
		free(data);
		return ;
	}
	data->line[0].x = x;
	data->line[0].y = y;
	if (abs(data->dx) > abs(data->dy))
		ft_algorithm_xcalc(data);
	else
		ft_algorithm_ycalc(data);
	free(data->line);
	free(data);
}
