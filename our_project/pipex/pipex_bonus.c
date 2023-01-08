/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:34:52 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/13 20:38:49 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	piper(t_pipex *all, char **argv, int *i)
{
	pid_t	pid;
	int		fd[2];

	pipe_and_fork(&fd, &pid);
	all->last_pid = pid;
	if (pid == CHILD)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		get_list(all, argv, (*i));
		exit(1);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];

	pipe_and_fork(&fd, &pid);
	if (pid == CHILD)
	{
		here_doc_input(&fd, limiter);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

int	main(int argc, char *argv[])
{
	t_pipex	all;
	int		i;
	int		res_status;

	i = 1;
	res_status = 0;
	get_path(&all);
	if (argc < 5)
		err_msg_fd("arguments invalid", 2, 1);
	if (ft_strnstr(argv[1], "here_doc", 8) != 0)
		opener(&all, argc, argv, 1);
	else
		opener(&all, argc, argv, 0);
	do_cmds(&all, argc - 2, argv, &i);
	while (i--)
	{
		if (all.last_pid == wait(&all.status))
			res_status = all.status;
	}
	free(all.n_av);
	return ((res_status >> 8) & 0xFF);
}
