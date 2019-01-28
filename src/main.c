/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 21:49:13 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/17 21:49:15 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	configuration(void)
{
	write(1, "-------------------------------------\n", 38);
	write(1, "MOVE XYZ   : 8 2 4 6 + - (numeric)   \n", 38);
	write(1, "FOV/ZOOM   : * / (numeric)           \n", 38);
	write(1, "ROTATE     : (Arrows, PgUp, PgDn)    \n", 38);
	write(1, "RESET      : 0 (numeric)             \n", 38);
	write(1, "-------------------------------------\n", 38);
}

int		init_mlx(t_mlx *mlx, t_scene *scene, t_obj **obj_pix)
{
	ft_bzero(mlx, sizeof(t_mlx));
	if (!(mlx->mlx_ptr = mlx_init()))
		return (ft_perror("Connection to the X server failed\n"));
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCR_WID, \
		SCR_HEI, "RTv1")))
		return (ft_perror("Impossible to create new window\n"));
	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SCR_WID, SCR_HEI)))
		return (ft_perror("Impossible to set up image\n"));
	mlx->data_add = mlx_get_data_addr(mlx->img_ptr, \
		&mlx->bpp, &mlx->s_line, &mlx->endian);
	ft_bzero(mlx->data_add, SCR_HEI * SCR_WID);
	mlx->scene = scene;
	mlx->light = scene->light;
	mlx->obj = scene->obj;
	mlx->asp_rat = (double)SCR_WID / (double)SCR_HEI;
	mlx->pix_obj = obj_pix;
	configuration();
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_scene	scene;
	t_mlx	mlx;
	t_obj	*obj_pix[SCR_HEI * SCR_WID];

	if (argc != 2)
		ft_usage("RTv1 scene");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(NULL);
	if (!ft_strequ(ft_strchr(argv[1], '.'), ".rt"))
		ft_error("Invalid file\n");
	if (!(parser(fd, &scene)))
		ft_error("Scene is incomplete or incorrect\n");
	close(fd);
	if (init_mlx(&mlx, &scene, &obj_pix[0]))
	{
		struct_del(&scene);
		exit(-1);
	}
	put_to_window(&mlx);
	mlx_hook(mlx.win_ptr, 2, 0, hook_keydown, (void *)&mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, exit_x, (void *)&mlx);
	mlx_hook(mlx.win_ptr, 4, 1L << 6, mouse_hook, (void *)&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
