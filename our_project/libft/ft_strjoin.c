/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:28:34 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/27 20:18:20 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	while (src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i == 0 && j == 0)
		return (ft_strdup(""));
	temp = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!temp)
		return (0);
	temp[0] = '\0';
	ft_strcat(temp, s1);
	ft_strcat(temp, s2);
	return (temp);
}

void	ft_addstr(char **dst, char *src)
{
	char	*tmp;

	tmp = *dst;
	*dst = ft_strjoin(tmp, src);
	free(tmp);
}
