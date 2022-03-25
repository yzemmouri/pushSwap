/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:16:46 by yoelguer          #+#    #+#             */
/*   Updated: 2019/10/23 23:29:14 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_there(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_copy(char **str, char **line)
{
	int		i;
	char	*ptr;
	char	*tmp;

	i = 0;
	ptr = *str;
	if (ft_is_there(ptr, '\n') == 0)
	{
		*line = ft_strdup(ptr);
		ft_strdel(str);
		return (1);
	}
	tmp = ft_strchr(*str, '\n');
	*tmp = '\0';
	*line = ft_strdup(*str);
	*str = ft_strdup(tmp + 1);
	ft_strdel(&ptr);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	t_get_next_line_vars	v;

	if (fd < 0 || fd > 4864 || read(fd, v.buff, 0) < 0)
		return (-1);
	if (!v.str[fd])
		v.str[fd] = ft_strnew(0);
	while (!ft_is_there(v.str[fd], '\n'))
	{
		v.ret = read(fd, v.buff, BUFF_SIZE);
		if (v.ret <= 0)
			break ;
		v.buff[v.ret] = '\0';
		v.ptr = v.str[fd];
		v.str[fd] = ft_strjoin(v.str[fd], v.buff);
		ft_strdel(&v.ptr);
		if (ft_is_there(v.str[fd], '\n') || v.ret < BUFF_SIZE)
			break ;
	}
	if (v.ret <= 0 && !*v.str[fd])
	{
		if (v.ret < 0)
			ft_strdel(&v.str[fd]);
		return (v.ret);
	}
	return (ft_copy(&v.str[fd], line));
}
