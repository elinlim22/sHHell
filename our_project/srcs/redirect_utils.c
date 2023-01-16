/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:42:10 by huipark           #+#    #+#             */
/*   Updated: 2023/01/16 21:37:13 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_unused_fd(t_cmd *cmd, int pid)
{
	if (pid == 0)
		close(cmd->fd[0]);
	else
	{
		close(cmd->fd[1]);
	}
}

char	*row_malloc(t_tok *tok)
{
	return(ft_strdup(tok->str));
}

void	ft_perror(char *file)
{
	printf("miniHell : %s: ", file);
	perror("");
}

void	reset_std_fd(t_cmd *cmd)
{
	dup2(cmd->STDOUT_FD, STDOUT_FILENO);
	dup2(cmd->STDIN_FD, STDIN_FILENO);
}
