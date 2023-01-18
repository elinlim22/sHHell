/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:38:43 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 13:56:03 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define READ 0
#define WRITE 1

void	red_check(t_cmd *cmd, t_red **curr_red)
{
	if (cmd->red->type == LEFT)
		*curr_red = cmd->red;
	else if (cmd->red->type == RIGT)
	{
		cmd->out_fd = open(cmd->red->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->out_fd == -1)
		{
			ft_strerror(cmd->red->str, errno);
		}
	}
	else if (cmd->red->type == DRGT)
	{
		cmd->out_fd = open(cmd->red->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_fd == -1)
			ft_strerror(cmd->red->str, errno);
	}
}

void	pipe_fd_handler(t_cmd *cmd)
{
	if (cmd->prev->fd[READ] != -2)
	{
		if (dup2(cmd->prev->fd[READ], STDIN_FILENO) == -1)
		{
			perror("miniHell : dup2 error");
			exit (1);
		}
		close(cmd->prev->fd[READ]);
	}
	if (cmd->next != NULL)
	{
		if (dup2(cmd->fd[WRITE], STDOUT_FILENO) == -1)
		{
			perror("miniHell : dup2 error");
			exit (1);
		}
		close(cmd->fd[WRITE]);
	}
}

void	fd_handler(t_cmd *cmd)
{
	t_red	*curr_red;

	pipe_fd_handler(cmd);
	curr_red = NULL;
	while (cmd->red->next)
	{
		cmd->red = cmd->red->next;
		red_check(cmd, &curr_red);
	}
	if (curr_red)
	{
		if (curr_red->type == LEFT)
		{
			cmd->in_fd = open(curr_red->str, O_RDONLY);
			if (cmd->in_fd == -1)
				ft_strerror(curr_red->str, errno);
			dup2(cmd->in_fd, STDIN_FILENO);
			close(cmd->in_fd);
		}
	}
	if (cmd->out_fd != -2)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}
