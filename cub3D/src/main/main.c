/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/19 17:34:26 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* static bool	check_img(void *mlx, void **image, char *path)
{
	int	width;
	int	height;

	*image = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!(*image))
		return (false);
	return (true);
} */

static bool	check_img(void *mlx, t_pic *image, char *path)
{
	(*image).mlx_img = mlx_xpm_file_to_image(mlx, path, &(*image).width, &(*image).height);
	if (!(*image).mlx_img)
		return (false);
	printf("texture path: %s, height = %d, width: %d\n", path, (*image).height, (*image).width);
	(*image).addr = mlx_get_data_addr((*image).mlx_img, &(*image).bits_pix,
		&(*image).line_len, &(*image).endian);
	if (!(*image).addr)
		return (mlx_destroy_image(mlx, (*image).mlx_img), false);
	return (true);
}

static bool	animated_sprit(void *mlx, t_map *tmap)
{
	if (tmap->count.animation > 3)
		tmap->count.animation = 0;
	if (tmap->sprite.mlx_img)
		mlx_destroy_image(mlx, tmap->sprite.mlx_img);
	if (tmap->count.animation == 0)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly1.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 1)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly2.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 2)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly3.xpm"))
			return (false);
	}
	else if (tmap->count.animation == 3)
	{
		if (!check_img(mlx, &tmap->sprite, "textures/KeyFly4.xpm"))
			return (false);
	}
	tmap->count.animation++;
	return (true);
}


static bool img_init(void *mlx, t_map *tmap)
{
	printf("loop image!\n");
	if (!check_img(mlx, &tmap->tex_e, tmap->path_e)
		|| !check_img(mlx, &tmap->tex_n, tmap->path_n) 
		|| !check_img(mlx, &tmap->tex_s, tmap->path_s)
		|| !check_img(mlx, &tmap->tex_w, tmap->path_w)
		|| !check_img(mlx, &tmap->door, "textures/Door1.xpm")
		|| !check_img(mlx, &tmap->door_open, "textures/Door11.xpm")
		|| !check_img(mlx, &tmap->sprite, "textures/KeyFly1.xpm"))
		return (false);
	return (true);
}

static bool player_init(t_map *tmap)
{
	tmap->player = malloc(sizeof(t_cam));
	if (!tmap->player)
	{
		print_err("Cube3D: malloc player");
		return (false);		
	}	
	tmap->player->ray2 = malloc(sizeof(t_raycastor));
	if (!tmap->player->ray2)
		return (print_err("Cube3D: malloc ray2"), false);
	tmap->player->ray2->offx = 0.0;
	tmap->player->ray2->offy = 0.0;
	tmap->player->planex = 0.66;
	tmap->player->planey = 0;
	tmap->player->pitch = 0.0;
	tmap->player->p_angle = get_player_angle(tmap);
	tmap->player->fov = 66.0 * (M_PI / 180);
	tmap->player->ray_nb = WIDTH;
	tmap->visible = 10;	
	tmap->player->dirx = tmap->count.map_dirx;
	tmap->player->diry = tmap->count.map_diry;
	tmap->player->posx = tmap->count.map_posx;
	tmap->player->posy = tmap->count.map_posy;
	return (true);
}


static int	loop_img(t_scene *scene)
{
	if (!scene->win)
		return (1);		
	//render_background(&scene->img, scene->tmap);
	draw_maps(scene);
	mouse_rotate(scene);
	//put_minimap(scene);
	//p.x = WIDTH / 2;
	//p.y = HEIGHT / 2;
	//map_to_img(&scene->img, scene->tmap, p);
	animated_sprit(scene->mlx, scene->tmap);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.mlx_img, 0, 0);

	//render_instructions(all);
	return (0);
}


int	main(int ac, char	**av)
{
	t_scene	scene;
	
	if (ac != 2)
		return (printf("Usage: ./cub3d valid_map.cub"));
	if (ft_parsing(av[1], &scene) != 0)
		return (free_map_data(scene.tmap), 1);
	scene.mlx = mlx_init();
	if (!scene.mlx)
		return (perror_and_exit(&scene, "Cube3D: mlx_init"), 1);
	scene.win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "Cube 3D");
	if (!scene.win)
		return (perror_and_exit(&scene, "Cube3D: mlx_new_window"), 1);
	if (!img_init(scene.mlx, scene.tmap))
		return (perror_and_exit(&scene, "Cannot load image"), 1);
	if (!player_init(scene.tmap))
		return (perror_and_exit(&scene, NULL), 1);
	scene.img.mlx_img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	if (!scene.img.mlx_img)
		return (perror_and_exit(&scene, "mlx_new_image"), 1);
	scene.img.addr = mlx_get_data_addr(scene.img.mlx_img, &scene.img.bits_pix,
		&scene.img.line_len, &scene.img.endian);
	hook_controls(&scene);
	mlx_loop_hook(scene.mlx, loop_img, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
