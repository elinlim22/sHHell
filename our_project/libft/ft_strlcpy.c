/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:48:39 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/15 17:56:36 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char **dest, const char *src, size_t size)

{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!size)
		return (len);
	if (!*dest)
		*dest = ft_wrap_malloc(size + 1);
	while (i + 1 < size && src[i] != '\0')
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	printf("(*dest) : %s\n", (*dest));
	return (len);
}
