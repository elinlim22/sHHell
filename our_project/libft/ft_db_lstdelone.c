/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db_lstdelone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:23:31 by hyeslim           #+#    #+#             */
/*   Updated: 2022/10/24 15:38:11 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_db_lstdelone(t_node *node)
{
	t_node	*p;
	t_node	*n;

	if (!node)
		return ;
	p = node->prev;
	n = node->next;
	p->next = n;
	n->prev = p;
	free(node);
}
