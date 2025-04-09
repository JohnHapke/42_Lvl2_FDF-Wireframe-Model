/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:34:38 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/09 11:29:53 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_prep_handler(char **argv, t_mlx_data *data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		error_handler(data, 0);
	ft_pars_handler(argv, data->map);
	data->iso = ft_calloc(1, sizeof(t_isometric));
	if (!data->iso)
		error_handler(data, 1);
	ft_to_isometric(data->map, data->iso);
	data->lines = ft_algorithm_handler(data->map, data->iso);
	if (!data->lines)
		error_handler(data, 2);
	ft_center_map(data->map, data->iso);
}

int	main(int argc, char **argv)
{
	t_mlx_data	*data;

	if (argc != 2)
		error_handler(NULL, 0);
	data = ft_calloc(1, sizeof(t_mlx_data));
	if (!data)
		error_handler(NULL, 0);
	ft_prep_handler(argv, data);
	data->mlx = mlx_init(800, 600, "FDF", false);
	if (!data->mlx)
		error_handler(data, 3);
	data->image = mlx_new_image(data->mlx, 800, 600);
	if (!data->image)
		error_handler(data, 3);
	data->offset_x = 0;
	data->offset_y = 0;
	data->scale = 1.0f;
	ft_mlx_handler(data);
	mlx_terminate(data->mlx);
	return (0);
}
