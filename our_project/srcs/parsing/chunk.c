/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:19:26 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/12 17:53:16 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sep_chunk(t_cmd **cmd, t_tok **tok)
{
	t_tok	*curr;
	t_tok	*temp;

	(*cmd)->tok = (t_tok *)malloc(sizeof(t_tok));
	init_tok(&((*cmd)->tok));
	(*cmd)->red = NULL;
	(*cmd)->next = NULL;
	curr = (*tok)->next;
	while (curr->next && curr->next->type != PIPE)
		curr = curr->next;
	if (curr->next && curr->next->type == PIPE)
	{
		temp = curr->next->next;
		free(curr->next->str);
		free(curr->next);
		curr->next = temp;
	}
	(*cmd)->tok->next = (*tok)->next;
	(*tok)->next = curr->next;
	curr->next = NULL;
}

static void	cmd_add(t_cmd **cmd, t_tok **tok)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return ;
	sep_chunk(&new, tok);
	(*cmd)->next = new;
	(*cmd) = (*cmd)->next;
}

t_cmd	*chunk(t_tok **tok)
{
	t_cmd	*cmd;
	t_cmd	*curr;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->tok = NULL;
	cmd->red = NULL;
	cmd->STDIN_FD = dup(STDIN_FILENO);
	cmd->STDOUT_FD = dup(STDOUT_FILENO);
	curr = cmd;
	while ((*tok)->next)
		cmd_add(&curr, tok);
	return (cmd);
}
