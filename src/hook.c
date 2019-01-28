/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 12:09:58 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		exit_x(void *mlx)
{
	t_mlx *m;

	m = (t_mlx *)mlx;
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	exit(0);
	return (0);
}

int		hook_keydown(int k, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (k == 53)
		exit_x(mlx);
	if (k == 84 || k == 86 || k == 88 || k == 91 || k == 69 || k == 78)
		ptr->selected ? translate(k, &(ptr->selected->tr_pos), 0) : \
	translate(k, &(ptr->scene->cam_transl), 1);
	if (k == 67 || k == 75)
		ptr->selected ? scale(k, &(ptr->selected->tr_siz), 0) : \
	scale(k, &(ptr->scene->fov), 1);
	if (k == 123 || k == 124 || k == 125 || k == 126 || k == 116 || k == 121)
		ptr->selected ? rotate(k, &(ptr->selected->tr_rot)) : \
	cam_rotate(k, &(ptr->scene->cam_angles));
	if (k == 82)
		reset(ptr);
	if (k == 87)
	{
		ptr->selected = NULL;
		return (0);
	}
	put_to_window(ptr);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (button == 1)
	{
		if (ptr->pix_obj[y * SCR_WID + x])
			ptr->selected = (ptr->pix_obj)[y * SCR_WID + x];
		else
			ptr->selected = NULL;
	}
	return (0);
}
