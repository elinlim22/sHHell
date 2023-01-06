/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:41:25 by huipark           #+#    #+#             */
/*   Updated: 2023/01/06 17:52:27 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_tok(t_tok *token)
{
	t_tok	*red_node;
	t_tok	*file_node;

	token = token->next;
	while (token->next != NULL)
	{
		if (token->next->type == LEFT || token->next->type == RIGT
			|| token->next->type == DLFT || token->next->type == DRGT)
		{
			if (token->next == NULL)
				return ;
			red_node = token->next;
			file_node = token->next->next;
			if (token->next->next->next != NULL)
				token->next = token->next->next->next;
			else
				token->next = NULL;
			free(red_node->str);
			free(red_node);
			free(file_node);
			if (token->next == NULL)
				break ;
		}
		if (token->next->type != LEFT && token->next->type != RIGT
			&& token->next->type != DLFT && token->next->type != DRGT)
			token = token->next;
	}
}
// asd qwe < fil2
/*
// cmd 1 cat -> null
// cmd 2 echp -> asdf -> null

// cmd 1 infile -> outfulrasd
// cmd 2 null
*/
static void	newnode(t_red *head, t_tok *token, int type)
{
	t_red	*newnode;

	while (head->next != NULL)
		head = head->next;
	newnode = ft_wrap_malloc(sizeof (t_red));
	newnode->str = token->str;
	newnode->type = type;
	newnode->next = NULL;
	head->next = newnode;
}

static void	explore_token(t_red *head, t_tok *token)
{
	int	type;

	while (token->next != NULL)
	{
		token = token->next;
		if (token->type == LEFT || token->type == RIGT
			|| token->type == DRGT || token->type == DLFT)
		{
			type = token->type;
			if (token->next == NULL)
				return ;
			token = token->next;
			newnode(head, token, type);
		}
	}
}

t_red	*init_red(t_tok	*token)
{
	t_red	*head;

	head = ft_wrap_malloc(sizeof(t_red));
	head->next = NULL;
	head->str = NULL;
	head->type = 0;
	explore_token(head, token);
	redirection_tok(token);
	return (head);
}
