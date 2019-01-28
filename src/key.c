/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:26:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:26:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	translate(int key, t_vector *pos, int cam)
{
	double	i;

	i = 1.5;
	if (key == 84)
		(*pos)[1] -= i;
	if (key == 86)
		(*pos)[0] -= i;
	if (key == 88)
		(*pos)[0] += i;
	if (key == 91)
		(*pos)[1] += i;
	i = cam ? -1.5 : 1.5;
	if (key == 69)
		(*pos)[2] += i;
	if (key == 78)
		(*pos)[2] -= i;
}

void	rotate(int key, t_vector *dir)
{
	double		k;
	t_matrix	m;

	k = DEG_TO_RAD(1);
	if (key == 126)
		x_rotate(&m, k);
	if (key == 125)
		x_rotate(&m, -k);
	if (key == 124)
		y_rotate(&m, k);
	if (key == 123)
		y_rotate(&m, -k);
	if (key == 116)
		z_rotate(&m, k);
	if (key == 121)
		z_rotate(&m, -k);
	dir_multipl(&m, dir);
	normilize_vec(dir);
}

void	cam_rotate(int key, t_vector *angles)
{
	double k;

	k = DEG_TO_RAD(1);
	if (key == 126)
		(*angles)[0] += k;
	if (key == 125)
		(*angles)[0] -= k;
	if (key == 124)
		(*angles)[1] += k;
	if (key == 123)
		(*angles)[1] -= k;
	if (key == 116)
		(*angles)[2] -= k;
	if (key == 121)
		(*angles)[2] += k;
}

void	scale(int key, double *siz, int cam)
{
	double	i;

	i = cam ? 0.1 : -1.0f;
	if (key == 67)
		*siz = ((*siz - i) < DEG_TO_RAD(0) && cam) ? DEG_TO_RAD(0) : *siz - i;
	if (key == 75)
	{
		if (((*siz + i) > 0 && !cam) || ((*siz + i) < DEG_TO_RAD(160) && cam))
			*siz += i;
		else
		{
			if (cam)
				*siz = DEG_TO_RAD(160);
			else
				*siz = 0;
		}
	}
}

void	reset(t_mlx *mlx)
{
	t_obj	*objs;
	t_scene	*scene;

	scene = mlx->scene;
	scene->cam_transl = (t_vector){0.0f, 0.0f, 0.0f};
	scene->cam_angles = (t_vector){0.0f, 0.0f, 0.0f};
	scene->fov = FOV;
	mlx->selected = NULL;
	objs = mlx->obj;
	while (objs)
	{
		objs->tr_pos = objs->pos;
		objs->tr_rot = objs->rot;
		objs->tr_siz = objs->size;
		objs = objs->next;
	}
}
