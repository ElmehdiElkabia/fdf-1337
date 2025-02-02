/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:02:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/02 21:53:06 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_fdf(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->window.mlx = mlx_init();
	if (!fdf->window.mlx)
		ft_destroy(fdf);
	fdf->window.win = mlx_new_window(fdf->window.mlx, WIDTH, HEIGHT, "FDF");
	if (!fdf->window.win)
		ft_destroy(fdf);
	fdf->image.img = mlx_new_image(fdf->window.mlx, WIDTH, HEIGHT);
	if (!fdf->image.img)
		ft_destroy(fdf);
	fdf->image.addr = mlx_get_data_addr(fdf->image.img,
			&fdf->image.bits_per_pixel, &fdf->image.line_length,
			&fdf->image.endian);
	if (!fdf->image.addr)
		ft_destroy(fdf);
}

void	init_camera(t_fdf *fdf)
{
	fdf->camera.zoom = 10;
	fdf->camera.angle_x = 0;
	fdf->camera.angle_y = 0;
	fdf->camera.angle_z = 1;
	fdf->camera.offset_x = fdf->camera.zoom * fdf->map.width / 2;
	fdf->camera.offset_y = fdf->camera.zoom * fdf->map.height / 2;
	fdf->camera.projection = 1;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		init_fdf(&fdf);
		init_map(argv[1], &fdf);
		parse_map(argv[1], &fdf);
		init_camera(&fdf);
		render_map(&fdf);
		mlx_key_hook(fdf.window.win, key_hook, &fdf);
		mlx_hook(fdf.window.win, 17, 0, ft_destroy, &fdf);
		mlx_loop(fdf.window.mlx);
		ft_destroy(&fdf);
	}
}
