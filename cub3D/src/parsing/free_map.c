/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: layang <layang@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:40:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/06/25 23:45:11 by layang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_map_data_2(t_map *tmap)
{
	if (tmap && tmap->door_state)
		free_arr((void ***)&tmap->door_state);
	if (tmap && tmap->door_timer)
		free_arr((void ***)&tmap->door_timer);
	if (tmap && tmap->order)
		free(tmap->order);
	free(tmap);
}

void	free_map_data(t_map *tmap)
{
	if (!tmap)
		return ;
	if (tmap && tmap->the_map)
		free_arr((void ***)&tmap->the_map);
	if (tmap && tmap->map_copy)
		free_arr((void ***)&tmap->the_map);
	if (tmap && tmap->path_e)
		free(tmap->path_e);
	if (tmap && tmap->path_n)
		free(tmap->path_n);
	if (tmap && tmap->path_s)
		free(tmap->path_s);
	if (tmap && tmap->path_w)
		free(tmap->path_w);
	if (tmap && tmap->player)
	{
		if (tmap->player && tmap->player->ray2)
			free(tmap->player->ray2);
		free(tmap->player);
	}
	free_map_data_2(tmap);
}

void	free_map_img(t_scene *scene)
{
	if (!scene->tmap)
		return ;
	if (scene->tmap->tex_n.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->tex_n.mlx_img);
	if (scene->tmap->tex_s.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->tex_s.mlx_img);
	if (scene->tmap->tex_w.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->tex_w.mlx_img);
	if (scene->tmap->tex_e.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->tex_e.mlx_img);
	if (scene->tmap->door.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->door.mlx_img);
	if (scene->tmap->sprite.mlx_img)
		mlx_destroy_image(scene->mlx, scene->tmap->sprite.mlx_img);
}
