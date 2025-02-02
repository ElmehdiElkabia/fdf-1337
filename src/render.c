/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 06:14:42 by marvin            #+#    #+#             */
/*   Updated: 2025/02/02 20:06:31 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_line_loop(t_point start, t_point end, t_fdf *fdf,
		t_bresenham bresenham)
{
	while (start.x != end.x || start.y != end.y)
	{
		bresenham.error2 = 2 * bresenham.error;
		if (bresenham.error2 >= -bresenham.dy)
		{
			bresenham.error -= bresenham.dy;
			start.x += bresenham.sx;
		}
		if (bresenham.error2 < bresenham.dx)
		{
			bresenham.error += bresenham.dx;
			start.y += bresenham.sy;
		}
		if (start.x >= 0 && start.x < WIDTH && start.y >= 0 && start.y < HEIGHT)
			my_mlx_pixel_put(&fdf->image, start.x, start.y, start.color);
	}
}

void	draw_line(t_point start, t_point end, t_fdf *fdf)
{
	t_bresenham	bresenham;

	ft_bzero(&bresenham, sizeof(t_bresenham));
	project_point(&start, fdf);
	project_point(&end, fdf);
	bresenham.dx = abs(end.x - start.x);
	if (start.x < end.x)
		bresenham.sx = 1;
	else
		bresenham.sx = -1;
	bresenham.dy = abs(end.y - start.y);
	if (start.y < end.y)
		bresenham.sy = 1;
	else
		bresenham.sy = -1;
	bresenham.error = bresenham.dx - bresenham.dy;
	draw_line_loop(start, end, fdf, bresenham);
}

void	clear_image(t_fdf *fdf)
{
	ft_bzero(fdf->image.addr, WIDTH * HEIGHT * (fdf->image.bits_per_pixel / 8));
}

void	render_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf->map.points[y][x], fdf->map.points[y][x + 1],
					fdf);
			if (y < fdf->map.height - 1)
				draw_line(fdf->map.points[y][x], fdf->map.points[y + 1][x],
					fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->window.mlx, fdf->window.win, fdf->image.img, 0,
		0);
}
