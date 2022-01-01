/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 01:11:51 by asimoes           #+#    #+#             */
/*   Updated: 2021/05/26 12:37:45 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# define MAX_FDS 4096

typedef struct s_fd_data {
	char	*buffer;
	short	eof;
}				t_fd_data;

int		get_next_line(int fd, char **line);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strncpy(char *s1, char *s2, size_t max);
size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char const *s1, char const *s2, unsigned int s2_len);

#endif