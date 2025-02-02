/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:27:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/02 18:37:07 by eelkabia         ###   ########.fr       */
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
	double		angle_x;
	double		angle_y;
	double		angle_z;
	int			offset_x;
	int			offset_y;
	int			projection;
}				t_camera;

typedef struct s_fdf
{
	t_map		map;
	t_window	window;
	t_image		image;
	t_camera	camera;
}				t_fdf;

typedef struct s_bresenham
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			error;
	int			error2;
}				t_bresenham;

void			parse_map(char *filename, t_fdf *fdf);
void			free_array(char **array);
void			init_map(char *filename, t_fdf *fdf);
void			render_map(t_fdf *fdf);
void			init_camera(t_fdf *fdf);
int				key_hook(int keycode, t_fdf *fdf);
int			ft_destroy(t_fdf *fdf);
void			project_point(t_point *point, t_fdf *fdf);
int				ft_atoi_base(const char *str, int base);
#endif
