/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:09:59 by huipark           #+#    #+#             */
/*   Updated: 2023/01/15 17:56:32 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strlcpy2(char *dest, const char *src, size_t size)
{
	size_t	len;

	if (!src)
		return (0);
	len = ft_strlen(src);
	if (size != 0)
	{
		while (*src && size > 1)
		{
			*dest = *src;
			dest++;
			src++;
			size--;
		}
		*dest = '\0';
	}
	return (len);
}

char	*check(char *line)
{
	int		i;
	char	*res;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	res = ft_strdup(&line[i + 1]);
	if (!res)
		return (NULL);
	line[i + 1] = '\0';
	return (res);
}

char	*get_read(int fd, char *backup)
{
	char	*buf;
	char	*temp_address;
	ssize_t	size;

	size = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (size)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || size == 0)
			break ;
		buf[size] = '\0';
		temp_address = backup;
		backup = ft_strjoin(backup, buf);
		free(temp_address);
		if (!backup || ft_strchr(backup, '\n'))
			break ;
	}
	free(buf);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_read(fd, backup);
	if (!line)
		return (NULL);
	backup = check(line);
	return (line);
}
