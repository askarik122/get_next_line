/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihestia <ihestia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:44:13 by ihestia           #+#    #+#             */
/*   Updated: 2019/05/13 23:21:08 by ihestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		function(int ret, char **s, char **tmp, char **line)
{
	int			len;

	len = 0;
	if (ret == 0 && (*s == NULL || **s == '\0'))
		return (0);
	while (*(*s + len) != '\n' && *(*s + len) != '\0')
		len++;
	if (*(*s + len) == '\0')
	{
		*line = ft_strdup(*s);
		ft_strdel(s);
		return (1);
	}
	if (*(*s + len) == '\n')
	{
		*line = ft_strsub(*s, 0, len);
		*tmp = ft_strdup(*s + len + 1);
		free(*s);
		*s = *tmp;
		if (s[0] == '\0')
			ft_strdel(s);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*s;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			ret;
	int			len;

	len = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s == NULL)
			s = ft_strnew(1);
		tmp = ft_strjoin(s, buf);
		free(s);
		s = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	len = function(ret, &s, &tmp, line);
	return (len);
}
