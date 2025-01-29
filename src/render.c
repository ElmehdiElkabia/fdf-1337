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


void	project_point(t_point *point, t_fdf *fdf)
{
	int		old_x;
	int		old_y;

	old_x = point->x;
	old_y = point->y;

	// Apply isometric projection
	point->x = (old_x - old_y) * cos(0.523599);
	point->y = (old_x + old_y) * sin(0.523599) - point->z;

	// Apply zoom
	point->x *= fdf->camera.zoom;
	point->y *= fdf->camera.zoom;

	// Apply centering
	point->x += fdf->camera.offset_x;
	point->y += fdf->camera.offset_y;
}

void	draw_line(t_point start, t_point end, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	int		error[2];

	project_point(&start, fdf);
	project_point(&end, fdf);
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

void	render_map(t_fdf *fdf)
{
	int		x;
	int		y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf->map.points[y][x],fdf->map.points[y][x + 1], fdf);
			if (y < fdf->map.height - 1)
				draw_line(fdf->map.points[y][x],fdf->map.points[y + 1][x], fdf);
			x++;
		}
		y++;
	}
}
