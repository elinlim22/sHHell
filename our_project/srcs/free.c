/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:39:09 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/11 20:52:04 by huipark          ###   ########.fr       */
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

void	free_export(t_env *copy_env)
{
	t_env	*prev_env;

	while (copy_env->prev)
	{
		prev_env = copy_env->prev;
		free(copy_env);
		copy_env = prev_env;
	}
}
