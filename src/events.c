/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <eelkabia@student.>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:47:08 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 03:47:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init_camera(t_fdf *fdf)
{
	fdf->camera.zoom = 10;
	fdf->camera.angle_x = 0.523599;
	fdf->camera.angle_y = 0.523599;
	fdf->camera.angle_z = 0.8;
	fdf->camera.offset_x = WIDTH * 0.2;
	fdf->camera.offset_y = HEIGHT * 0.2;
}