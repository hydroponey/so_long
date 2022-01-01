/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 01:21:41 by asimoes           #+#    #+#             */
/*   Updated: 2021/05/26 12:38:06 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*gnl_strncpy(char *s1, char *s2, size_t max)
{
	char	*newstr;
	size_t	newlen;
	size_t	i;
	size_t	j;

	if (!s1)
		newlen = gnl_strlen(s2);
	else
		newlen = gnl_strlen(s1) + max;
	newstr = (char *)malloc(sizeof(char) * (newlen + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (*s1)
			newstr[i++] = (*s1++);
	}
	j = 0;
	while (j < max)
		newstr[i++] = s2[j++];
	newstr[i] = 0;
	return (newstr);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if ((char)c == p[i])
		return (&p[i]);
	return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2, unsigned int s2_len)
{
	unsigned int	len;
	unsigned int	i;
	char			*joined;

	if (!s1)
		return (gnl_strncpy(NULL, (char *)s2, s2_len));
	len = gnl_strlen(s1) + s2_len;
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}
