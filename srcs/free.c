/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:03:26 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/30 00:52:18 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include "solong.h"

#ifdef LINUX

void	free_config(t_conf *conf)
{
	int	i;

	free_paths(conf);
	free_textures(conf);
	if (conf->mlx != NULL && conf->window != NULL)
		mlx_destroy_window(conf->mlx, conf->window);
	i = 0;
	while (i < conf->map_height)
	{
		if (conf->map != NULL && i < conf->map_alloc_lines)
			free(conf->map[i]);
		if (conf->text_map != NULL)
			free(conf->text_map[i]);
		i++;
	}
	free(conf->sprites);
	free(conf->z_buffer);
	free(conf->map);
	free(conf->text_map);
	if (conf->mlx != NULL)
	{
		mlx_destroy_display(conf->mlx);
		free(conf->mlx);
	}
}

#else

void	free_config(t_conf *conf)
{
	int	i;

	//free_textures(conf);
	if (conf->mlx != 0 && conf->window != 0)
		mlx_destroy_window(conf->mlx, conf->window);
	i = 0;
	while (i < conf->height)
	{
		if (conf->map != 0 && i < conf->alloc_lines)
			free(conf->map[i]);
		if (conf->text_map != 0)
			free(conf->text_map[i]);
		i++;
	}
	free(conf->map);
	free(conf->text_map);
	if (conf->mlx != 0)
	{
		free(conf->mlx);
	}
}

#endif