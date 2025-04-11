/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:00:39 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/11 10:13:12 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup(t_mlx_data *data)
{
	if (!data)
		return ;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->lines)
		free_wires(data->map, data->lines);
	if (data->map || data->iso)
		free_map(data->map, data->iso);
	free(data);
}

void	error_handler(t_mlx_data *data, t_error_code code)
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
	cleanup(data);
	exit(1);
}

void	ft_control_map(t_map *map, char **value)
{
	int	column_count;

	column_count = 0;
	while (value[column_count] != NULL)
		column_count++;
	if (map->ymax == 0)
		map->xmax = column_count;
	else if (column_count != map->xmax)
		error_handler(NULL, ERROR_PARSING);
}
