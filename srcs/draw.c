/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 22:53:13 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/30 00:51:33 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "minilibx-linux/mlx.h"

void	draw_map(t_conf *conf)
{
	mlx_put_image_to_window(conf->mlx, conf->window, conf->img, 0, 0);
}