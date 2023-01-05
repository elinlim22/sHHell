/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:30:27 by huipark           #+#    #+#             */
/*   Updated: 2023/01/05 17:44:49 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_wrap_malloc(size_t s)
{
	void	*ret;

	ret = malloc(s);
	if (ret == NULL)
		exit (1);
	return (ret);
}
