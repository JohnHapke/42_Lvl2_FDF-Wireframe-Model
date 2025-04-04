/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:02:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/04 11:56:57 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_callback(mlx_key_data_t keydata, void *param)
{
	t_mlx_data	*data;

	data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

void	ft_close_callback(void *param)
{
	t_mlx_data	*data;

	data = (t_mlx_data *)param;
	cleanup(data);
	exit(0);
}

void	ft_mlx_image(t_mlx_data *data, int i, int j)
{
	int	x;
	int	y;
	int	scale;
	int	offset_x;
	int	offset_y;

	scale = 40;
	offset_x = 400;
	offset_y = 300;
	x = (data->lines[i]->line[j].x * scale) + offset_x;
	y = (data->lines[i]->line[j].y * scale) + offset_y;
	if (x >= 0 && x <= 800 && y >= 0 && y <= 600)
		mlx_put_pixel(data->image, x, y, 0xFFFFFFFF);
}

void	ft_mlx_handler(t_mlx_data *data)
{
	int	i;
	int	j;
	int	line_count;
	int	size;

	line_count = (data->map->xmax - 1) * (data->map->ymax)
		+ (data->map->xmax) * (data->map->ymax - 1);
	i = -1;
	while (++i < line_count)
	{
		if (data->lines[i])
		{
			size = abs(data->lines[i]->dy);
			if (data->lines[i]->dx > size)
				size = abs(data->lines[i]->dx);
		}
		j = -1;
		while (++j <= size)
		{
			ft_mlx_image(data, i, j);
			printf("Line %d, Punkt %d: x=%d, y=%d\n", i, j, 
				data->lines[i]->line[j].x, data->lines[i]->line[j].y);
		}
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		error_handler(data, 3);
	mlx_key_hook(data->mlx, &ft_key_callback, data);
	mlx_close_hook(data->mlx, &ft_close_callback, data);
	mlx_loop(data->mlx);
}
