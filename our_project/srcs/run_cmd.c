/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:58:35 by huipark           #+#    #+#             */
/*   Updated: 2023/01/12 15:2406 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define READ 0
#define WRITE 1

char	*row_malloc(t_tok *tok)
{
	return(ft_strdup(tok->str));
}

void	ft_perror(char *file)
{
	printf("miniHell : %s: ", file);
	perror("");
}

void	close_unused_fd(t_cmd *cmd, int pid)
{
	if (pid == 0)
	{
		close(cmd->fd[READ]);
	}
	else
		close(cmd->fd[WRITE]);
}

char	**get_cmd(t_cmd *cmd)
{
	t_tok	*head;
	char	**temp;
	int		row;
	int		col;

	head = cmd->tok;
	col = 0;
	row = 0;
	while (cmd->tok->next)
	{
		cmd->tok = cmd->tok->next;
		col++;
	}
	temp = (char **)ft_wrap_malloc(sizeof(char *) * (col + 1));
	cmd->tok = head;
	while (cmd->tok->next)
	{
		cmd->tok = cmd->tok->next;
		temp[row++] = row_malloc(cmd->tok);
	}
	temp[row] = NULL;
	return (temp);
}

char	*get_vaild_cmd(char **path, char *cmd)
{
	int		i;
	char	*temp_address;
	char	*temp_path;
	char	*temp_cmd;

	i = 0;
	temp_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	temp_cmd = ft_strjoin("/", cmd);
	if (!temp_cmd)
		exit (1);
	while (path[i])
	{
		temp_address = temp_path;
		temp_path = ft_strjoin(path[i], temp_cmd);
		free (temp_address);
		if (access(temp_path, X_OK) == 0)
			return (temp_path);
		i++;
	}
	return (NULL);
}

char	**get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			envp[i] += 5;
			break ;
		}
		i++;
	}
	return (ft_split(envp[i], ':'));
}

void	reset_std_fd(t_cmd *cmd)
{
	dup2(cmd->STDOUT_FD, STDOUT_FILENO);
	dup2(cmd->STDIN_FD, STDIN_FILENO);
}

void	red_check(t_cmd *cmd, char **stdin)
{
	if (cmd->red->type == LEFT)
			*stdin = cmd->red->str;
	else if (cmd->red->type == RIGT)
	{
		cmd->out_fd = open(cmd->red->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->out_fd == -1)
			ft_perror(cmd->red->str);
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
	char	*stdin;

	pipe_fd_handler(cmd);
	stdin = NULL;
	while (cmd->red->next)
	{
		cmd->red = cmd->red->next;
		red_check(cmd, &stdin);
	}
	if (stdin)
	{
		cmd->in_fd = open(stdin, O_RDONLY);
		if (cmd->in_fd == -1)
			ft_perror(stdin);
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != -2)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
}

void	execute(t_cmd *cmd, char *envp[])
{
	char	**command;
	char	**path;

	command = get_cmd(cmd);
	path = get_path(envp);
	command[0] = get_vaild_cmd(path, command[0]);
	execve(command[0], command, envp);
}

int	do_cmd(t_cmd *cmd, t_env env, char *envp[], int pid)
{
	fd_handler(cmd);
	if (pid == 0)
		close_unused_fd(cmd, pid);
	if (cmd->tok->next)
	{
		if (!ft_strcmp(cmd->tok->next->str, "export"))
			run_export(cmd->tok->next, env);
		else if (!ft_strcmp(cmd->tok->next->str, "exit"))
			exit_check(cmd->tok->next);
		else if (!ft_strcmp(cmd->tok->next->str, "env"))
			print_env(cmd->tok->next, env);
		else if (!ft_strcmp(cmd->tok->next->str, "unset"))
			run_unset(cmd->tok->next, &env);
		else if (!ft_strcmp(cmd->tok->next->str, "pwd"))
			return (run_pwd());
		else if (!ft_strcmp(cmd->tok->next->str, "echo"))
			say_it(cmd->tok->next);
		else if (!ft_strcmp(cmd->tok->next->str, "cd"))
			cd(cmd->tok->next->next, &env);
	}
	execute(cmd, envp);
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->tok->next)
	{
		if (!ft_strcmp(cmd->tok->next->str, "export"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "exit"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "env"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "unset"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "pwd"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "echo"))
			return (1);
		else if (!ft_strcmp(cmd->tok->next->str, "cd"))
			return (1);
	}
	return (0);
}

void	run_cmd(t_cmd *cmd, t_env env, char *envp[])
{
	t_cmd	*head;
	int		pid;
	int		exit_status;

	head = cmd;
	pid = 1;
	if (!cmd->red && !cmd->tok && cmd->next)	//cmd가 헤드일 경우
		cmd = cmd->next;
	if (!cmd->next && is_builtin(cmd))
	{
		do_cmd(cmd, env, envp, pid);
	}
	else
	{
		while (cmd)
		{
			if (pipe(cmd->fd) == -1)
				perror("miniHell : pipe error");
			pid = fork();
			if (pid == -1)
				perror("miniHell : fork_error");
			else if (pid == 0)
			{
				exit_status = do_cmd(cmd, env, envp, pid);
				exit(exit_status);
			}
			else
			{
				close_unused_fd(cmd, pid);
				cmd = cmd->next;
			}
		}
	}

	cmd = head;
	reset_std_fd(cmd);
	// else
	// 	do_child
}
