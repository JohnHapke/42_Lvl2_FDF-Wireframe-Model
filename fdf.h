/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:15:30 by jhapke            #+#    #+#             */
/*   Updated: 2025/04/10 12:09:50 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include <MLX42/MLX42_Int.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define MY_PI 3.14159265359

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_map
{
	t_point	**points;
	int		xmax;
	int		ymax;
	int		zmin;
	int		zmax;
}	t_map;

typedef struct s_line_data
{
	t_point	*line;
	int		dx;
	int		dy;
	int		y_step;
	int		x_step;
	int		size;
}	t_line_data;

typedef struct s_isometric
{
	t_point	**isometric;
}	t_isometric;

typedef struct s_mlx_data
{
	t_map		*map;
	t_isometric	*iso;
	t_line_data	**lines;
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			offset_x;
	int			offset_y;
	float		scale;
}	t_mlx_data;

// parsing
void		ft_pars_handler(char **argv, t_map *map);
void		ft_pars_array_counter(int fds, t_map *map);
void		ft_pars_mem_allocation(t_map *map);
void		ft_pars_fdf_file(int fds, t_map *map);
void		ft_find_z_range(t_map *maps);

// memory liberation & error checking
void		ft_free(char **ar);
void		error_handler(t_mlx_data *data, int i);
void		free_map(t_map	*map, t_isometric *iso);
void		free_wires(t_map *map, t_line_data **lines);
void		cleanup(t_mlx_data *data);
void		ft_lines_free(t_line_data **lines, int line_count);
void		ft_control_map(t_map *map);

//mlx_management
void		ft_key_callback(mlx_key_data_t keydata, void *param);
void		ft_close_callback(void *param);
void		ft_mlx_handler(t_mlx_data *data);
void		ft_mlx_image(t_mlx_data *data, int i, int j);
void		ft_mlx_render(t_mlx_data *data);

// algorithm
void		ft_algorithm_xcalc(t_line_data *data);
void		ft_algorithm_ycalc(t_line_data *data);
void		ft_algorithm_row(t_line_data **data, t_isometric *iso,
				int i, int j);
void		ft_algorithm_col(t_line_data **data,
				t_isometric *iso, int i, int j);
t_line_data	**ft_algorithm_handler(t_map *map, t_isometric *iso);
t_line_data	**ft_algorithm_m(t_map *map, t_isometric *iso,
				t_line_data **lines, int line_count);

// isometric
void		ft_to_isometric(t_map *map, t_isometric *iso);
void		ft_isometric_calc(t_map *map, t_isometric *iso, int i);
void		ft_center_map(t_map *map, t_isometric *iso);
double		ft_z_scale(t_map *map);

//visual
void		ft_offset_map(t_map *map, t_isometric *iso, double border[4]);
void		ft_center_map(t_map *map, t_isometric *iso);
uint32_t	ft_get_color_by_height(float z, t_map *maps);
uint32_t	fix_endianness(uint32_t color);

//main
void		ft_prep_handler(char **argv, t_mlx_data *data);

#endif