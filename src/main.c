/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:34:38 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/21 16:27:05 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_prep_handler(char **argv, t_mlx_data *data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		ft_error_handler(data, ERROR_MEMORY_ALLOC);
	ft_parsing_handler(argv, data->map);
	data->iso = ft_calloc(1, sizeof(t_isometric));
	if (!data->iso)
		ft_error_handler(data, ERROR_ISOMETRIC_ALLOC);
	ft_to_isometric(data->map, data->iso);
	data->lines = ft_algorithm_handler(data->map, data->iso);
	if (!data->lines)
		ft_error_handler(data, ERROR_BRESENHAM);
	ft_center_map(data->map, data->iso);
}

int	main(int argc, char **argv)
{
	t_mlx_data	*data;

	if (argc != 2)
		ft_error_handler(NULL, ERROR_USAGE);
	data = ft_calloc(1, sizeof(t_mlx_data));
	if (!data)
		ft_error_handler(NULL, ERROR_MEMORY_ALLOC);
	ft_prep_handler(argv, data);
	data->mlx = mlx_init(1800, 1600, "FDF", false);
	if (!data->mlx)
		ft_error_handler(data, ERROR_MLX_INIT);
	data->image = mlx_new_image(data->mlx, 1800, 1600);
	if (!data->image)
		ft_error_handler(data, ERROR_MLX_INIT);
	data->offset_x = 0;
	data->offset_y = 0;
	data->scale = 1.0f;
	ft_mlx_handler(data);
	mlx_terminate(data->mlx);
	return (0);
}
