/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:22:21 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 12:42:53 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_red(t_cmd *cmd)
{
	t_red	*newnode;

	if (cmd->red == NULL)
	{
		newnode = ft_wrap_malloc(sizeof (t_red));
		newnode->str = NULL;
		newnode->type = 0;
		newnode->next = NULL;
		cmd->red = newnode;
	}
}

void	init_red(t_cmd	*cmd)
{
	explore_token(cmd);
	redirection_tok(cmd);
}

void	add_tok(t_tok **tok, char *str, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->next = NULL;
	(*tok)->next = new;
	(*tok) = (*tok)->next;
}

void	init_tok(t_tok **tok)
{
	(*tok)->next = NULL;
	(*tok)->str = NULL;
	(*tok)->type = 0;
}
