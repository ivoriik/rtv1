/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:19:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/21 16:11:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			put_to_window(t_mlx *ptr)
{
	ft_bzero(ptr->data_add, (size_t)(SCR_HEI * ptr->s_line));
	mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
	render(ptr, ptr->scene);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img_ptr, 0, 0);
}

unsigned int	get_rgb(unsigned int red, unsigned int green, unsigned int blue)
{
	unsigned int color;

	color = red;
	color = (color << 8) + green;
	color = (color << 8) + blue;
	return (color);
}

void			img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char *data;

	color = mlx_get_color_value(mlx->mlx_ptr, color);
	if (!(x >= 0 && x < SCR_WID && y >= 0 && y < SCR_HEI))
		return ;
	data = mlx->data_add;
	data += y * mlx->s_line + mlx->bpp / 8 * x;
	ft_memcpy(data, &color, sizeof(color));
}
