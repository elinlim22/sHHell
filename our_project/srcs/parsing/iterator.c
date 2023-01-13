/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:41:25 by huipark           #+#    #+#             */
/*   Updated: 2023/01/13 22:10:37 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	search_red_type(t_tok *token)
{
	t_tok	*red_node;
	t_tok	*file_node;

	if (!token->next)
		return (1);
	if ((token->next->type == LEFT || token->next->type == RIGT
			|| token->next->type == DLFT || token->next->type == DRGT))
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

static void	newnode(t_cmd *cmd, t_tok *token, int type)
{
	t_red	*newnode;
	t_red	*temp_head;

	temp_head = cmd->red;
	newnode = ft_wrap_malloc(sizeof (t_red));
	while (cmd->red->next != NULL)
		cmd->red = cmd->red->next;
	newnode->str = token->str;
	newnode->type = type;
	newnode->next = NULL;
	cmd->red->next = newnode;
	cmd->red = temp_head;
}

void	redirection_tok(t_cmd *cmd)
{
	t_tok	*temp_head;

	while (cmd != NULL)
	{
		temp_head = cmd->tok;
		while (cmd->tok != NULL)
		{
			if (search_red_type(cmd->tok))
				break ;
			if (cmd->tok->next->type != LEFT && cmd->tok->next->type != RIGT
				&& cmd->tok->next->type != DLFT && cmd->tok->next->type != DRGT)
				cmd->tok = cmd->tok->next;
		}
		cmd->tok = temp_head;
		cmd = cmd->next;
	}
}

void	explore_token(t_cmd *cmd)
{
	int		type;
	t_tok	*temp_head;

	type = 0;
	cmd = cmd->next;
	while (cmd != NULL)
	{
		add_red(cmd);
		temp_head = cmd->tok;
		while (cmd->tok != NULL)
		{
			if (cmd->tok->type == LEFT || cmd->tok->type == RIGT
				|| cmd->tok->type == DRGT || cmd->tok->type == DLFT)
			{
				type = cmd->tok->type;
				if (cmd->tok->next == NULL)
					return ;
				cmd->tok = cmd->tok->next;
				newnode(cmd, cmd->tok, type);
			}
			cmd->tok = cmd->tok->next;
		}
		cmd->tok = temp_head;
		cmd = cmd->next;
	}
}
