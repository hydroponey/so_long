/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:13:12 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/30 20:32:55 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_collectible {
	int	x;
	int	y;
	short int collected;
}	t_collectible;

typedef struct s_conf {
	int				fd;
	void			*mlx;
	void			*window;
	void			*img;
	int				*img_data;
	int				screen_height;
	int				screen_width;
	int				move_count;
	double			posy;
	double			posx;
	int				width;
	int				height;
	char			**text_map;
	int				**map;
	int				lines;
	int				alloc_lines;
	int				exit_x;
	int				exit_y;
	short int		start_found;
	short int		exit_found;
	t_collectible	**collectibles;
}	t_conf;

void	exit_error(char *err, t_conf *conf);
void	check_args(int argc, char *argv[], t_conf *conf);
void	parse_map(t_conf *conf);
void	load_textures(t_conf *conf);
void	get_textures_addr(t_conf *conf);
void    draw_map(t_conf *conf);
void	*cube_realloc(void *ptr, size_t size, size_t ptrsize);

#endif