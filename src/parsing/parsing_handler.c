/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:50:01 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/15 15:41:27 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parsing_handler(char **argv, t_map *map)
{
	int		fds;

	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
		ft_error_handler(NULL, ERROR_OPEN);
	ft_parse_array_counter(fds, map);
	close(fds);
	if (fds < 0)
		ft_error_handler(NULL, ERROR_CLOSE);
	fds = open(argv[1], O_RDONLY);
	if (fds < 0)
		ft_error_handler(NULL, ERROR_OPEN);
	ft_parse_fdf_file(fds, map);
	close(fds);
	if (fds < 0)
		ft_error_handler(NULL, ERROR_CLOSE);
	ft_find_z_range(map);
}
