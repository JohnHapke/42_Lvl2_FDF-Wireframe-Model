/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:00:39 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/10 11:44:56 by jhapke           ###   ########.fr       */
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

void	error_handler(t_mlx_data *data, int code)
{
	if (code == 0)
		write(2, "Error: Usage: ./fdf <filename>.fdf\n", 35);
	else if (code == 1)
		write(2, "Error: Failed to allocate isometric data\n", 41);
	else if (code == 2)
		write(2, "Error: Failed to generate wireframe lines\n", 42);
	else if (code == 3)
		write(2, "Error: Failed to initialize MLX resources\n", 42);
	else
		write(2, "Error: Unknown error occurred\n", 30);
	cleanup(data);
	exit(1);
}
