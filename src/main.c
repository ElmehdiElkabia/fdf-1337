/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:02:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/01/27 06:13:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_destroy(t_fdf *fdf)
{
	if (fdf->window.win)
		mlx_destroy_window(fdf->window.mlx, fdf->window.win);
	if (fdf->image.img)
		mlx_destroy_image(fdf->window.mlx, fdf->image.img);
}

void	init_fdf(t_fdf *fdf)
{
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

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		ft_destroy(fdf);
		exit(0);
	}
	return (0);
}
	 	//printf("keycode: %d\n", keycode);

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		init_fdf(&fdf);
		init_map(argv[1], &fdf);
		parse_map(argv[1], &fdf);
		render_map(&fdf);
		mlx_key_hook(fdf.window.win, key_hook, &fdf);
		mlx_loop(fdf.window.mlx);
		ft_destroy(&fdf); 
	}
}
// int	i = 0;
// int	j = 0;
// while (i < fdf.map.height)
// {
// 	j = 0;
// 	while (j < fdf.map.width)
// 	{
// 		printf("x: %d, y: %d, z: %d, color: %d\n", fdf.map.points[i][j].x,
				// fdf.map.points[i][j].y, fdf.map.points[i][j].z,
				// fdf.map.points[i][j].color);
// 		j++;
// 	}
// 	i++;
// }