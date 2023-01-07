/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:41:25 by huipark           #+#    #+#             */
/*   Updated: 2023/01/07 13:24:34 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_red_type(t_tok *token)
{
	t_tok	*red_node;
	t_tok	*file_node;

	if (token->next->type == LEFT || token->next->type == RIGT
		|| token->next->type == DLFT || token->next->type == DRGT)
	{
		if (token->next->next == NULL)
			return (1);
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
			return (1);
	}
	return (0);
}

void	redirection_tok(t_tok *token)
{
	token = token->next;
	while (token->next != NULL)
	{
		if (search_red_type(token))
			return ;
		if (token->next->type != LEFT && token->next->type != RIGT
			&& token->next->type != DLFT && token->next->type != DRGT)
			token = token->next;
	}
}

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
