/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:49:01 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/13 20:41:33 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	opener(t_pipex *all, int argc, char **argv, int p_case);
void	pipe_and_fork(int (*fd)[2], pid_t *pid);
void	here_doc_input(int (*fd)[2], char *limiter);
void	fork_last(t_pipex *all);
void	do_cmds(t_pipex *all, int end, char **argv, int *i);

void	opener(t_pipex *all, int argc, char **argv, int p_case)
{
	if (p_case == 1)
	{
		all->hd = 1;
		all->fd.out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (all->fd.out == -1)
		{
			perror(argv[argc - 1]);
			exit(1);
		}
		here_doc(argv[2]);
	}
	else if (p_case == 0)
	{
		all->hd = 0;
		all->fd.out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		all->fd.in = open(argv[1], O_RDONLY, 0644);
		if (all->fd.out == -1 && all->fd.in == -1)
		{
			perror(argv[argc - 1]);
			perror(argv[1]);
			exit(1);
		}
		dup2(all->fd.in, STDIN_FILENO);
	}
}

void	pipe_and_fork(int (*fd)[2], pid_t *pid)
{
	if (pipe(*fd) == -1)
		err_msg_fd("pipe error", 2, 1);
	*pid = fork();
	if (*pid == -1)
		err_msg_fd("fork error", 2, 1);
}

void	here_doc_input(int (*fd)[2], char *limiter)
{
	char	*line;

	close((*fd)[0]);
	line = get_next_line(STDIN_FILENO);
	while (ft_strnstr(line, limiter, ft_strlen(limiter)) == 0)
	{
		ft_putstr_fd(line, (*fd)[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
}

void	fork_last(t_pipex *all)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(all->cmd, all->n_av, environ);
		perror(all->cmd);
		exit(1);
	}
}

void	do_cmds(t_pipex *all, int end, char **argv, int *i)
{
	while (++(*i) + all->hd <= end)
	{
		all->n_av = NULL;
		if ((*i) + all->hd != end)
			piper(all, argv, i);
		else
		{
			dup2(all->fd.out, STDOUT_FILENO);
			get_list(all, argv, (*i));
			fork_last(all);
		}
		free(all->cmd);
	}
}
