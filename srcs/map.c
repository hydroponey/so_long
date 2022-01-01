/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 22:02:28 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/30 20:33:45 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

int	get_max_width(t_conf *conf)
{
	int		i;
	int		max_width;
	int		len;

	max_width = -1;
	i = 0;
	while (i < conf->lines)
	{
		len = ft_strlen(conf->text_map[i]);
		if (max_width < len)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	add_map_line(t_conf *conf, char *line)
{
	int		old_size;
	int		new_size;

	old_size = sizeof(char *) * conf->lines;
	new_size = sizeof(char *) * (conf->lines + 1);
	conf->text_map = cube_realloc(conf->text_map, new_size, old_size);
	if (!conf->text_map)
	{
		free(line);
		exit_error("realloc error.", conf);
	}
	conf->text_map[conf->lines] = ft_strdup(line);
	if (!conf->text_map[conf->lines])
	{
		free(line);
		exit_error("strdup error.", conf);
	}
	conf->lines++;
}

void	set_start_dir(t_conf *conf, int x, int y)
{
	if (x == 0 || y == 0)
		exit_error("Starting position can not be on a border.", conf);
	conf->map[x][y] = 0;
	conf->posy = y + 0.5;
	conf->posx = x + 0.5;
}

void	transform_line(t_conf *conf, int x)
{
	int		y;
	int		len;
	char	c;

	y = 0;
	ft_memset(conf->map[x], -1, sizeof(int) * conf->width);
	len = ft_strlen(conf->text_map[x]);
	while (y < len)
	{
		c = conf->text_map[x][y];
		if (c == ' ')
			conf->map[x][y] = -1;
		else if (c == '0' || c == '1')
			conf->map[x][y] = c - 48;
		else if (c == 'C')
			conf->map[x][y] = 2;
		else if (c == 'P')
		{
			if (conf->start_found)
				exit_error("Multiple starting positions in map.", conf);
			set_start_dir(conf, x, y);
			conf->start_found = 1;
		}
		else if (c == 'E')
		{
			if (conf->exit_found)
				exit_error("Multiple exit positions in map.", conf);
			conf->map[x][y] = 0;
			conf->exit_x = x;
			conf->exit_y = y;
			conf->exit_found = 1;
		}
		else
			exit_error("Unsupported character found in map.", conf);
		y++;
	}
}

void	transform_map(t_conf *conf)
{
	int	width;
	int	x;

	width = get_max_width(conf);
	conf->alloc_lines = 0;
	conf->width = width;
	conf->height = conf->lines;
	conf->map = (int **)malloc(sizeof(int *) * conf->lines);
	if (!conf->map)
		exit_error("Malloc error.", conf);
	x = 0;
	while (x < conf->lines)
	{
		conf->map[x] = malloc(sizeof(int) * width);
		if (!conf->map[x])
			exit_error("Malloc error.", conf);
		conf->alloc_lines++;
		transform_line(conf, x);
		x++;
	}
	if (conf->start_found == 0)
		exit_error("No starting position found.", conf);
}

void	*cube_realloc(void *ptr, size_t size, size_t ptrsize)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, ptrsize);
		free(ptr);
	}
	return (new);
}

void	check_line(t_conf *conf, char *line)
{
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
	{
		free(line);
		exit_error("Malloc error in check_line.", conf);
	}
	len = ft_strlen(trimmed);
	free(trimmed);
	if (len > 0)
		add_map_line(conf, line);
}

void	parse_map(t_conf *conf)
{
	int		ret;
	char	*line;

	ret = get_next_line(conf->fd, &line);
	while (ret >= 0)
	{
		check_line(conf, line);
		free(line);
		if (ret == 0 || ret == -1)
			break ;
		ret = get_next_line(conf->fd, &line);
	}
	transform_map(conf);
	//check_map(conf);
}
