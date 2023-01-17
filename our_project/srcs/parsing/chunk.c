/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:19:26 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/18 00:20:24 by huipark          ###   ########.fr       */
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
	(*cmd)->stdin_fd = -2;
	(*cmd)->stdout_fd = -2;
	(*cmd)->in_fd = -2;
	(*cmd)->out_fd = -2;
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
	new->prev = (*cmd);
	(*cmd) = (*cmd)->next;
}

t_cmd	*chunk(t_tok **tok)
{
	t_cmd	*cmd;
	t_cmd	*curr;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->tok = NULL;
	cmd->red = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->stdin_fd = dup(STDIN_FILENO);
	cmd->stdout_fd = dup(STDOUT_FILENO);
	cmd->fd[0] = -2;
	cmd->fd[1] = -2;
	cmd->in_fd = -2;
	cmd->out_fd = -2;
	curr = cmd;
	while ((*tok)->next)
		cmd_add(&curr, tok);
	free(*tok);
	return (cmd);
}
