/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 06:14:42 by marvin            #+#    #+#             */
/*   Updated: 2025/01/27 06:14:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_line(t_point start, t_point end, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	int		error[2];

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = start.x < end.x ? 1 : -1;
	sign.y = start.y < end.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	while (start.x != end.x || start.y != end.y)
	{
		mlx_pixel_put(fdf->window.mlx, fdf->window.win, start.x, start.y, start.color);
		 error[1] = error[0] * 2;
		if (error[1] >= -delta.y)
		{
			error[0] -= delta.y;
			start.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			start.y += sign.y;
		}
	}
}

t_point	project_point(t_point point, t_fdf *fdf)
{
	t_point	proj;


	proj.x = (point.x - point.y) * cos(0.5);
	proj.y = (point.x + point.y) * sin(0.5) - point.z;

	// Apply zoom
	proj.x *= fdf->camera.zoom;
	proj.y *= fdf->camera.zoom;

	// Apply centering
	proj.x += fdf->camera.offset_x;
	proj.y += fdf->camera.offset_y;

	proj.z = point.z;
	proj.color = point.color;
	return (proj);
}

void	render_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	point;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			point = project_point(fdf->map.points[y][x], fdf);
			if (x < fdf->map.width - 1)
				draw_line(point, project_point(fdf->map.points[y][x + 1], fdf), fdf);
			if (y < fdf->map.height - 1)
				draw_line(point, project_point(fdf->map.points[y + 1][x], fdf), fdf);
			x++;
		}
		y++;
	}
}
