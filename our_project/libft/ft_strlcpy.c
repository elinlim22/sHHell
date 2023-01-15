/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:48:39 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/15 19:19:43 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char **dest, const char *src, size_t size)

{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!size)
		return (len);
	if (!*dest)
		*dest = ft_wrap_malloc(size);
	while (i + 1 < size && src[i] != '\0')
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	return (len);
}
