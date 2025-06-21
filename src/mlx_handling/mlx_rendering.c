/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:30:06 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:30:23 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_image(t_mlx_data *data, int i, int j)
{
	int			x;
	int			y;
	int			offset_x;
	int			offset_y;
	uint32_t	color;

	color = ft_get_color_by_height(data->lines[i]->line[j].z, data->map);
	offset_x = 1800;
	offset_y = 1600;
	x = (int)(data->lines[i]->line[j].x * data->scale)
		+ (offset_x / 2) + data->offset_x;
	y = (int)(data->lines[i]->line[j].y * data->scale)
		+ (offset_y / 2) + data->offset_y;
	if (x >= 0 && x < offset_x && y >= 0 && y < offset_y)
		mlx_put_pixel(data->image, x, y, color);
}

void	ft_mlx_render(t_mlx_data *data)
{
	int	i;
	int	j;
	int	line_count;
	int	size;

	line_count = (data->map->xmax - 1) * (data->map->ymax)
		+ (data->map->xmax) * (data->map->ymax - 1);
	ft_memset(data->image->pixels, 0, data->image->width
		* data->image->height * sizeof(uint32_t));
	i = -1;
	while (++i < line_count)
	{
		if (data->lines[i])
		{
			size = abs(data->lines[i]->dy);
			if (abs((data->lines[i]->dx)) > size)
				size = abs((int)data->lines[i]->dx);
		}
		j = -1;
		while (++j <= size)
		{
			if (j < data->lines[i]->size)
				ft_mlx_image(data, i, j);
		}
	}
}
