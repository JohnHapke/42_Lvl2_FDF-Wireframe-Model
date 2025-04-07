/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:34:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/07 10:45:01 by jhapke           ###   ########.fr       */
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
		if (er < 0)
		{
			data->line[i + 1].x = data->line[i].x + data->x_step;
			er += 2 * abs(data->dx);
		}
		else
			data->line[i + 1].x = data->line[i].x;
	}
}

void	ft_algorithm_row(t_line_data **data, t_isometric *iso, int i, int j)
{
	int	size;

	*data = malloc(sizeof(t_line_data));
	if (!*data)
		return ;
	(*data)->dy = (int)round(iso->isometric[i][j + 1].y
			- iso->isometric[i][j].y);
	(*data)->dx = (int)round(iso->isometric[i][j + 1].x
			- iso->isometric[i][j].x);
	size = abs((*data)->dy);
	if (abs((*data)->dx) > size)
		size = abs((*data)->dx);
	(*data)->line = malloc((size + 1) * sizeof(t_point));
	if (!(*data)->line)
	{
		free(*data);
		*data = NULL;
		return ;
	}
	(*data)->line[0].x = (int)round(iso->isometric[i][j].x);
	(*data)->line[0].y = (int)round(iso->isometric[i][j].y);
	if (abs((*data)->dx) > abs((*data)->dy))
		ft_algorithm_xcalc((*data));
	else
		ft_algorithm_ycalc((*data));
}

void	ft_algorithm_col(t_line_data **data, t_isometric *iso, int i, int j)
{
	int	size;

	*data = malloc(sizeof(t_line_data));
	if (!(*data))
		return ;
	(*data)->dy = (int)round(iso->isometric[i + 1][j].y
			- iso->isometric[i][j].y);
	(*data)->dx = (int)round(iso->isometric[i + 1][j].x
			- iso->isometric[i][j].x);
	size = abs((*data)->dy);
	if (abs((*data)->dx) > size)
		size = abs((*data)->dx);
	(*data)->line = malloc((size + 1) * sizeof(t_point));
	if (!((*data)->line))
	{
		free(*data);
		*data = NULL;
		return ;
	}
	(*data)->line[0].y = (int)round(iso->isometric[i][j].y);
	(*data)->line[0].x = (int)round(iso->isometric[i][j].x);
	if (abs((*data)->dx) > abs((*data)->dy))
		ft_algorithm_xcalc((*data));
	else
		ft_algorithm_ycalc((*data));
}

t_line_data	**ft_algorithm_handler(t_map *map, t_isometric *iso)
{
	t_line_data	**lines;
	int			i;
	int			line_count;

	line_count = (map->xmax - 1) * (map->ymax) + (map->xmax) * (map->ymax - 1);
	lines = ft_calloc(line_count, sizeof(t_line_data *));
	if (!lines)
	{
		error_handler(NULL, 2);
		return (NULL);
	}
	i = -1;
	while (++i < line_count)
		lines[i] = NULL;
	if (!ft_algorithm_m(map, iso, lines, 0))
	{
		return (NULL);
		ft_lines_free(lines, line_count);
	}
	return (lines);
}

t_line_data	**ft_algorithm_m(t_map *map, t_isometric *iso, t_line_data **lines, int line_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->ymax)
	{
		j = -1;
		while (++j < map->xmax)
		{
			if (j < map->xmax - 1)
			{
				ft_algorithm_row(&lines[line_count], iso, i, j);
				if (!lines[line_count])
				{
					ft_lines_free(lines, line_count);
					error_handler(NULL, 2);
				}
				line_count++;
			}
			if (i < map->ymax - 1)
			{
				ft_algorithm_col(&lines[line_count], iso, i, j);
				if (!lines[line_count])
				{
					ft_lines_free(lines, line_count);
					error_handler(NULL, 2);
				}
				line_count++;
			}
		}
	}
	return (lines);
}
