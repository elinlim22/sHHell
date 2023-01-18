/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:42:10 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 13:56:00 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_unused_fd(t_cmd *cmd, int pid)
{
	if (pid == 0)
		close(cmd->fd[0]);
	else
		close(cmd->fd[1]);
}

char	*row_malloc(t_tok *tok)
{
	return (ft_strdup(tok->str));
}

void	ft_strerror(char *file, int num)
{
	printf("miniHell : %s: %s\n", file, strerror(num));
	exit(1);
}

void	reset_std_fd(t_cmd *cmd, t_cmd *head)
{
	cmd = head;
	dup2(cmd->stdout_fd, STDOUT_FILENO);
	dup2(cmd->stdin_fd, STDIN_FILENO);
}

void	last_fd_close(t_cmd *cmd)
{
	if (cmd->prev->fd[0] != -2)
	{
		close(cmd->prev->fd[0]);
		close(cmd->fd[0]);
	}
	else
		close(cmd->fd[0]);
}
