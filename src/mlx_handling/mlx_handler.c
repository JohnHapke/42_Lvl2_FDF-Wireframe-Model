/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:02:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:30:32 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_handler(t_mlx_data *data)
{
	ft_mlx_render(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error_handler(data, ERROR_MLX_INIT);
	mlx_key_hook(data->mlx, &ft_key_callback, data);
	mlx_close_hook(data->mlx, &ft_close_callback, data);
	mlx_loop(data->mlx);
}
