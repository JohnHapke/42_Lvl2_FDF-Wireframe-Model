/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:30 by jhapke            #+#    #+#             */
/*   Updated: 2025/03/26 11:18:18 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_map
{
	t_point	**points;
	int		xmax;
	int		ymax;
}	t_map;

// parsing

void	ft_input_handler(char **argv, t_map *map);
void	ft_array_counter(int fds, t_map *map);
void	ft_mem_allocation(t_map *map);
void	ft_parse_fdf_file(int fds, t_map *map);

// memory liberation

void	ft_free(char **ar);


#endif