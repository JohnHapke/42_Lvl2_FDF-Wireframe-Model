/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:00:39 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/21 16:28:53 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_cleanup(t_mlx_data *data)
{
	if (!data)
		return ;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->lines)
		ft_free_wires(data->map, data->lines);
	if (data->map || data->iso)
		ft_free_map(data->map, data->iso);
	free(data);
}

void	ft_error_handler(t_mlx_data *data, t_error_code code)
{
	if (code == ERROR_USAGE)
		write(2, "Error: Usage: ./fdf <filename>.fdf\n", 35);
	else if (code == ERROR_ISOMETRIC_ALLOC)
		write(2, "Error: Failed to allocate isometric data\n", 41);
	else if (code == ERROR_BRESENHAM)
		write(2, "Error: Failed to generate wireframe lines\n", 42);
	else if (code == ERROR_MLX_INIT)
		write(2, "Error: Failed to initialize MLX resources\n", 42);
	else if (code == ERROR_PARSING)
		write(2, "Error: Failed to parse map file or invalid map format\n", 54);
	else if (code == ERROR_MEMORY_ALLOC)
		write(2, "Error: Memory allocation failed\n", 32);
	else if (code == ERROR_OPEN)
		write(2, "Error: Failed to open file\n", 27);
	else if (code == ERROR_CLOSE)
		write(2, "Error: Failed to close file\n", 28);
	ft_cleanup(data);
	exit(1);
}
