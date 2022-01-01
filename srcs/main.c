/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:11:02 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/31 23:19:15 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include "solong.h"

void	exit_error(char *err, t_conf *conf)
{
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (conf->mlx)
		mlx_destroy_display(conf->mlx);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char *argv[], t_conf *conf)
{
	size_t	len;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ./so_long <map.ber>\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	len = ft_strlen(argv[1]);
	if (len <= 4)
		exit_error("Error: Map name is too short.\n", conf);
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
		exit_error("Error: Map name does not end with .ber.\n", conf);
	conf->fd = open(argv[1], O_RDONLY);
	if (conf->fd == -1)
	{
		ft_putstr_fd("Error: Can not open ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(".\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	parse_map(conf);
	close(conf->fd);
}

void	create_image(t_conf *conf)
{
	int	bpp;
	int	endian;
	int	sl;

	printf("map height: %d\nmap width: %d\nratio: %d\n", conf->height, conf->width, conf->width/conf->height);

	conf->img = mlx_new_image(conf->mlx, conf->screen_width, conf->screen_height);
	if (!conf->img)
		exit_error("[create_image] mlx_new_image failed", conf);
	conf->img_data = (int *)mlx_get_data_addr(conf->img, &bpp, &sl, &endian);
	if (!conf->img_data)
		exit_error("[create_image] mlx_get_data_addr failed", conf);
}

int	count_collectibles(t_conf *conf)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	x = 0;
	while (x < conf->height)
	{
		y = 0;
		while (y < conf->width)
		{
			if (conf->map[x][y] == 2)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

void	set_screen_size(t_conf *conf)
{
	int	x;
	int	y;

	if (mlx_get_screen_size(conf->mlx, &x, &y) == 0)
		exit_error("failed to get screen size", conf);
	
	x /= 2;
	y /= 2;
	printf("screen x: %d y: %d\n", x, y);
	printf("ratio: %d\n", x / y);
}

void	init_game(t_conf *conf)
{
	int	c_count;

	conf->mlx = mlx_init();
	if (!conf->mlx)
		exit_error("mlx_init failed.", conf);
	//load_textures(conf);
	//get_textures_addr(conf);
	c_count = count_collectibles(conf);
	conf->collectibles = (t_collectible**)malloc(sizeof(t_collectible *) * c_count);
	printf("collectibles: %d\n", c_count);
	if (!conf->collectibles)
		exit_error("[init_game] malloc error for collectibles", conf);
	set_screen_size(conf);
	create_image(conf);
	draw_map(conf);
}

int	main(int argc, char *argv[])
{
	t_conf	conf;

	ft_bzero(&conf, sizeof(t_conf));
	check_args(argc, argv, &conf);
	init_game(&conf);
	return (0);
}
