/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:10:20 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/12 17:38:48 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *s, char c)
{
	int	len;

	len = 0;
	while (s[len])
	{
		if (s[len] == c)
			break ;
		len++;
	}
	return (len);
}

static int	ft_count(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
		}
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**ft_free_all(char **s, int i)
{
	while (--i >= 0)
	{
		free(s[i]);
	}
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*temp;
	int		i;

	temp = (char *)s;
	res = (char **)malloc(sizeof(char *) * (ft_count(temp, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	res[ft_count(temp, c)] = 0;
	while (*temp)
	{
		while (*temp && *temp == c)
			temp++;
		if (*temp == 0)
			break ;
		res[i] = ft_substr(temp, 0, ft_len(temp, c));
		if (!res[i])
			return (ft_free_all(res, i));
		i++;
		temp += ft_len(temp, c);
	}
	return (res);
}

// void	free_all(char ***str)
// {
// 	int	len;

// 	len = ft_strlen_db(*str);
// 	while (--len)
// 		free((*str)[len]);
// 	free((*str)[0]);
// 	free(*str);
// }
