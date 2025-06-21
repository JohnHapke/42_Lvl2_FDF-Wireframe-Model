/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:28:07 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:31:04 by jhapke           ###   ########.fr       */
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
	ft_cleanup(data);
	exit(0);
}
