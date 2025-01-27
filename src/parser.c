/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:06:00 by marvin            #+#    #+#             */
/*   Updated: 2025/01/27 05:54:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	get_points(t_fdf *fdf, int i, int j, char **array)
{
	char	**z_color;

	z_color = ft_split(array[j], ',');
	if (z_color[1])
		fdf->map.points[i][j].color = ft_atoi_base(z_color[1] + 2,
				"0123456789ABCDEF");
	else
		fdf->map.points[i][j].color = 0xFFFFFF;
	fdf->map.points[i][j].x = j;
	fdf->map.points[i][j].y = i;
	fdf->map.points[i][j].z = ft_atoi(z_color[0]);
	free_array(z_color);
}

void	get_dimensions(char *str, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**array;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return ;
	fdf->map.width = 0;
	fdf->map.height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (fdf->map.height == 0)
		{
			array = ft_split(line, ' ');
			while (array[fdf->map.width])
				fdf->map.width++;
			free_array(array);
		}
		fdf->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_map(char *filename, t_fdf *fdf)
{
	int	i;

	i = 0;
	get_dimensions(filename, fdf);
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->map.points)
		return ;
	while (i < fdf->map.height)
	{
		fdf->map.points[i] = (t_point *)malloc(sizeof(t_point)
				* fdf->map.width);
		if (!fdf->map.points[i])
			return ;
		i++;
	}
}

void	parse_map(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**array;
	int		y;
	int		x;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	y = 0;
	while (y < fdf->map.height)
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		x = 0;
		while (x < fdf->map.width)
		{
			get_points(fdf, y, x, array);
			x++;
		}
		free_array(array);
		free(line);
		y++;
	}
}
