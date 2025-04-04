/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:00:39 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/04 10:27:52 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void cleanup(t_mlx_data *data)
{
    if (!data) return;
    
    if (data->image)
        mlx_delete_image(data->mlx, data->image);
    
    if (data->mlx)
        mlx_terminate(data->mlx);
    
    if (data->lines)
        free_wires(data->map, data->lines);
    
    if (data->map || data->iso)// Test
        free_map(data->map, data->iso);
    
    free(data);
}

void	error_handler(t_mlx_data *data, int code)
{
	if (code == 0)//usage
		write(2, "Error: Usage: ./fdf <filename>.fdf\n", 35);
	else if (code == 1)//iso
		write(2, "Error: Failed to allocate isometric data\n", 41);
	else if (code == 2)//wireframe lines
		write(2, "Error: Failed to generate wireframe lines\n", 42);
	else if (code == 3)//MLX
		write(2, "Error: Failed to initialize MLX resources\n", 42);
	else
		write(2, "Error: Unknown error occurred\n", 30);
	cleanup(data);
	exit(1);
}

void	ft_free(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return ;
	while (ar[i])
		free(ar[i++]);
	free(ar);
}

void	free_map(t_map	*map, t_isometric *iso)
{
	int	i;

	if (iso && map)
	{
		i = -1;
		while (++i < map->ymax)
			free(iso->isometric[i]);
		free(iso->isometric);
		free(iso);
	}
	i = -1;
	if (map)
	{
		while (++i < map->ymax)
			free(map->points[i]);
		free(map->points);
		free(map);
	}
}

void	free_wires(t_map *map, t_line_data **lines)
{
	int	i;
	int	lines_count;

	lines_count = (map->xmax - 1) * (map->ymax)
		+ (map->xmax) * (map->ymax - 1);
	if (lines)
	{
		i = -1;
		while (++i < lines_count)
		{
			free(lines[i]->line);
			free(lines[i]);
		}
		free(lines);
	}
}
