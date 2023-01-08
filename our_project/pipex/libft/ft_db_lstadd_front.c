/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db_lstadd_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:00:59 by hyeslim           #+#    #+#             */
/*   Updated: 2022/10/23 19:20:30 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_db_lstadd_front(t_node **head, t_node *new)
{
	t_node	*curr;

	if (*head == NULL)
		*head = new;
	else
	{
		curr = (*head)->next;
		new->prev = *head;
		new->next = curr;
		curr->prev = new;
		(*head)->next = new;
	}
}
