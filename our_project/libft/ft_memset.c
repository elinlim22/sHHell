/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:23:20 by hyeslim           #+#    #+#             */
/*   Updated: 2022/07/11 18:13:31 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;
	char	c;

	i = 0;
	c = (unsigned char)value;
	while (i < num)
	{
		((unsigned char *)ptr)[i] = c;
		i++;
	}
	return (ptr);
}
