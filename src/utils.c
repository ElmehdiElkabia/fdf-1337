/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:28:50 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/02 22:56:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	rotate_point(t_point *point, t_fdf *fdf)
{
	double temp_x;
	double temp_y;
	double temp_z;

	//rotate x
	temp_y = point->y * cos(fdf->camera.angle_y) - point->z * sin(fdf->camera.angle_y);
	temp_z = point->y * sin(fdf->camera.angle_y) + point->z * cos(fdf->camera.angle_y);
	point->y = temp_y;
	point->z = temp_z;

	//rotate y
	temp_x = point->x * cos(fdf->camera.angle_x) + point->z * sin(fdf->camera.angle_x);
	temp_z = -point->x * sin(fdf->camera.angle_x) + point->z * cos(fdf->camera.angle_x);
	point->x = temp_x;
	point->z = temp_z;

	//rotate z
	temp_x = point->x * cos(fdf->camera.angle_z) - point->y * sin(fdf->camera.angle_z);
	temp_y = point->x * sin(fdf->camera.angle_z) + point->y * cos(fdf->camera.angle_z);
	point->x = temp_x;
	point->y = temp_y;
}

void	project_point(t_point *point, t_fdf *fdf)
{
	point->x = (point->x * fdf->camera.zoom) + fdf->camera.offset_x;
	point->y = (point->y * fdf->camera.zoom) + fdf->camera.offset_y;
	point->x += WIDTH / 2 + fdf->camera.offset_x;
	point->y += HEIGHT / 4 + fdf->camera.offset_y;
	if (fdf->camera.projection == 1)
	{
		point->x = (point->x - point->y) * cos(0.9);
		point->y = (point->x + point->y) * sin(0.9) - point->z;
	}
	else if (fdf->camera.projection == 0)
	{
		point->x = point->x;
		point->y = point->y;
	}
	rotate_point(point, fdf);
}

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

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	value;

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			value = *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			value = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			value = *str - 'a' + 10;
		else
			break ;
		result = result * base + value;
		str++;
	}
	return (result);
}
