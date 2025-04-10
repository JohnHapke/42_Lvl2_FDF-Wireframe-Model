/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:02:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/10 12:10:04 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_callback(mlx_key_data_t keydata, void *param)
{
	t_mlx_data	*data;
	int			move_step;
	float		scale_step;

	move_step = 10;
	scale_step = 0.1f;
	data = (t_mlx_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->offset_x -= move_step;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->offset_x += move_step;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		data->offset_y -= move_step;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		data->offset_y += move_step;
	if (keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_EQUAL)
		data->scale += scale_step;
	if (keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_MINUS)
		data->scale -= scale_step;
	ft_mlx_render(data);
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
	memset(data->image->pixels, 0, data->image->width
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

void	ft_mlx_handler(t_mlx_data *data)
{
	ft_mlx_render(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		error_handler(data, 3);
	mlx_key_hook(data->mlx, &ft_key_callback, data);
	mlx_close_hook(data->mlx, &ft_close_callback, data);
	mlx_loop(data->mlx);
}
