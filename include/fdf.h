/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:27:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/01/27 06:30:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
// # include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct s_map
{
	int			width;
	int			height;
	t_point		**points;
}				t_map;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_window
{
	void		*mlx;
	void		*win;
}				t_window;

typedef struct s_camera
{
	int			zoom;
	int			angle_x;
	int			angle_y;
	int			angle_z;
	int			offset_x;
	int			offset_y;
}				t_camera;

typedef struct s_fdf
{
	t_map		map;
	t_window	window;
	t_image		image;
	t_camera	camera;
}				t_fdf;

void			parse_map(char *filename, t_fdf *fdf);
void			free_array(char **array);
void	init_map(char *filename, t_fdf *fdf);
void			render_map(t_fdf *fdf);
#endif
