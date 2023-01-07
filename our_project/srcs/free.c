/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:39:09 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/07 20:39:14 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next_cmd;
	t_tok	*next_tok;
	t_red	*next_red;

	while(cmd != NULL)
	{
		next_cmd = cmd->next;
		while (cmd->tok)
		{
			next_tok = cmd->tok->next;
			free(cmd->tok->str);
			free(cmd->tok);
			cmd->tok = next_tok;
		}
		while (cmd->red)
		{
			next_red = cmd->red->next;
			free(cmd->red->str);
			free(cmd->red);
			cmd->red = next_red;
		}
		free(cmd);
		cmd = next_cmd;
	}
}
