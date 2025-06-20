/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:21:11 by layang            #+#    #+#             */
/*   Updated: 2025/06/19 17:34:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_arr(char	***paths)
{
	int	i;

	i = 0;
	if (!paths || !*paths || !**paths)
		return ;
	while ((*paths)[i])
	{
		if ((*paths)[i])
			free((*paths)[i]);
		i++;
	}
	free(*paths);
	*paths = NULL;
}

/* void	free_lst(t_lmap	**tokens)
{
	t_lmap	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		if (tmp->line)
		{
			free(tmp->line);
			tmp->line = NULL;
		}
		*tokens = (*tokens)->next;
		free(tmp);
	}
	*tokens = NULL;
} */

int	close_cube3d(t_scene *scene)
{
	if (!scene)
		return (0);
	if (scene->win)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		scene->win = NULL;
	}
	if (scene->img.mlx_img)
		mlx_destroy_image(scene->mlx, scene->img.mlx_img);
	if (scene->tmap)
	{
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
		if (scene->tmap->door_open.mlx_img)
			mlx_destroy_image(scene->mlx, scene->tmap->door_open.mlx_img);
		if (scene->tmap->sprite.mlx_img)
			mlx_destroy_image(scene->mlx, scene->tmap->sprite.mlx_img);
		free_map_data(scene->tmap);
	}
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}	
	exit (1);
    return (0);
}


