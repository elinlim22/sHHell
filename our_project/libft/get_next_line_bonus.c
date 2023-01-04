/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:27:08 by hyeslim           #+#    #+#             */
/*   Updated: 2022/11/18 19:19:33 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_line(int fd, char *buff, char *backup)
{
	int		size;
	char	*tmp_pnt;

	size = 1;
	while (size)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		if (size == 0)
			break ;
		if (!backup)
			backup = ft_strdup("");
		buff[size] = '\0';
		tmp_pnt = backup;
		backup = ft_strjoin(tmp_pnt, buff);
		if (!backup)
			return (NULL);
		free(tmp_pnt);
		tmp_pnt = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_update(char *temp)
{
	char	*update;
	int		i;

	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\0')
		return (NULL);
	update = ft_substr(temp, i + 1, ft_strlen(temp) - i - 1);
	if (!update || update[0] == '\0')
	{
		free(update);
		update = NULL;
		return (NULL);
	}
	temp[i + 1] = '\0';
	return (update);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*buff;
	char		*temp;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff || fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	temp = ft_line(fd, buff, backup[fd]);
	free(buff);
	buff = NULL;
	if (!temp)
		return (NULL);
	backup[fd] = ft_update(temp);
	return (temp);
}
