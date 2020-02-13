/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaouhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:12:22 by dhaouhao          #+#    #+#             */
/*   Updated: 2020/02/09 02:12:26 by dhaouhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_line_break(char *stock)
{
	while (*stock)
		if (*(stock++) == '\n')
			return (1);
	return (0);
}

void	ft_fill_static(char **stock, char *buf)
{
	char	*tmp;

	tmp = *stock;
	*stock = ft_strdup(buf);
	free(tmp);
	free(buf);
}

int		ft_read_file(char **stock, int fd)
{
	char		*buffer;
	int			ret;

	if (!(buffer = malloc(sizeof(char) * 2)) || read(fd, buffer, 0) < 0)
		return (-1);
	if (*stock == NULL)
		*stock = ft_strdup("");
	while (!ft_line_break(*stock) && (ret = read(fd, buffer, 1)) > 0)
	{
		buffer[ret] = '\0';
		ft_fill_static(stock, ft_strjoin(*stock, buffer));
	}
	free(buffer);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*stock;
	int				ret;
	int				i;
	size_t			len;

	if (fd < 0 || line == NULL || (ret = ft_read_file(&stock, fd)) < 0)
		return (-1);
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	*line = ft_substr(stock, 0, i);
	len = ft_strlen(stock) - ft_strlen(*line);
	ft_fill_static(&stock, ft_substr(stock, ++i, len));
	ret = ((ret == 0 && len > 0) || ret > 0) ? 1 : ret;
	if (ret <= 0)
	{
		free(stock);
		stock = NULL;
	}
	return (ret);
}
