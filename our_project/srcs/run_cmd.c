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
#include "../includes/get_next_line.h"

#define READ 0
#define WRITE 1

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
	return (cmd);
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

void	here_doc(t_cmd *cmd)
{
	char	*line;
	int		fd;

	fd = open(".temp_here_doc", O_RDWR | O_CREAT | O_TRUNC , 0644);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		if (!line || !ft_strcmp(line, cmd->red->str))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close (fd);
	exit(0);
}
void	here_doc_check(t_cmd *cmd)
{
	t_red	*red_head;
	int		pid;

	red_head = cmd->red;
	while(cmd->red->next)
	{
		cmd->red = cmd->red->next;
		if (cmd->red->type == DLFT)
		{
			pid = fork();
			if (pid == -1)
				perror("miniHell : fork_error");
			else if (pid == 0)
				here_doc(cmd);
			else
			{
				free(cmd->red->str);
				cmd->red->str = ft_strdup(".temp_here_doc");
				cmd->red->type = LEFT;
				while (wait (0) != -1)
					;
			}
		}
	}
	cmd->red = red_head;
}

void	execute(t_cmd *cmd, char *envp[])
{
	char	**command;
	char	**path;

	command = get_cmd(cmd);
	path = get_path(envp);
	command[0] = get_vaild_cmd(path, command[0]);
	execve(command[0], command, envp);
	printf("miniHell : %s: command not found\n", command[0]);
	exit (127);
}

int	do_cmd(t_cmd *cmd, t_env env, char *envp[], int pid)
{
	fd_handler(cmd);
	if (pid == 0)
		close_unused_fd(cmd, pid);
	if (cmd->tok->next)
	{
		if (!ft_strcmp(cmd->tok->next->str, "export"))
			return (run_export(cmd->tok->next, env));
		else if (!ft_strcmp(cmd->tok->next->str, "exit"))
			return (exit_check(cmd->tok->next, cmd));
		else if (!ft_strcmp(cmd->tok->next->str, "env"))
			return (print_env(cmd->tok->next, env));
		else if (!ft_strcmp(cmd->tok->next->str, "unset"))
			return (run_unset(cmd->tok->next, &env));
		else if (!ft_strcmp(cmd->tok->next->str, "pwd"))
			return (run_pwd());
		else if (!ft_strcmp(cmd->tok->next->str, "echo"))
			return (say_it(cmd->tok->next));
		else if (!ft_strcmp(cmd->tok->next->str, "cd"))
			return (cd(cmd->tok->next->next, &env));
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

	head = cmd;
	pid = 1;
	if (!cmd->next->next && is_builtin(cmd->next))
		g_exit_status = do_cmd(cmd->next, env, envp, pid);
	else
	{
		cmd = cmd->next;
		while (cmd)
		{
			here_doc_check(cmd);
			if (pipe(cmd->fd) == -1)
				perror("miniHell : pipe error");
			pid = fork();
			if (pid == -1)
				perror("miniHell : fork_error");
			else if (pid == 0)
			{
				g_exit_status = do_cmd(cmd, env, envp, pid);
				exit(g_exit_status);
			}
			else
			{
				close_unused_fd(cmd, pid);
				cmd = cmd->next;
			}
		}
		while (wait(&g_exit_status) != -1)
			;
		g_exit_status = WEXITSTATUS(g_exit_status);
	}
	cmd = head;
	reset_std_fd(cmd);
}
