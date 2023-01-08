/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:35:12 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/13 19:18:48 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define CHILD (0)

typedef struct s_fd
{
	int	in;
	int	out;
}				t_fd;

typedef struct s_pipex
{
	int		hd;
	t_fd	fd;
	char	*cmd;
	char	**list_path;
	char	**n_av;
	pid_t	last_pid;
	int		status;
}				t_pipex;

extern char	**environ;

// pipex.c
void	piper(t_pipex *all, char **argv, int *i);
void	here_doc(char *limiter);

// utils.c
void	get_cmd(char **cmd, char *argv, char **list);
void	get_path(t_pipex *pipe);
void	get_av(t_pipex *all, char *argv);
void	get_list(t_pipex *all, char **argv, int i);

// utils2.c
void	opener(t_pipex *all, int argc, char **argv, int p_case);
void	pipe_and_fork(int (*fd)[2], pid_t *pid);
void	here_doc_input(int (*fd)[2], char *limiter);
void	fork_last(t_pipex *all);
void	do_cmds(t_pipex *all, int end, char **argv, int *i);

#endif
