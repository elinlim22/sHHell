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

#include "../../includes/minishell.h"

#define READ 0
#define WRITE 1
#define UNLINK 0
#define HEREDOG 1

void	execute(t_cmd *cmd, char *envp[], t_env *env)
{
	char	**command;
	char	**path;

	command = get_cmd(cmd);
	path = get_path(env);
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
	execute(cmd, envp, &env);
	return (0);
}

static void	parent_or_child(int pid, t_cmd *cmd, t_env env, char *envp[])
{
	if (pid == -1)
		perror("miniHell : fork_error");
	else if (pid == 0)
	{
		handle_signal_while_cmd();
		g_exit_status = do_cmd(cmd, env, envp, pid);
		exit(g_exit_status);
	}
	else
	{
		close_unused_fd(cmd, pid);
		if (cmd->prev->prev)
			close(cmd->prev->prev->fd[READ]);
	}
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
	t_cmd		*head;
	int			pid;

	head = cmd;
	pid = 1;
	if (!cmd->next->next && is_builtin(cmd->next))
		g_exit_status = do_cmd(cmd->next, env, envp, pid);
	else
	{
		while (cmd->next)
		{
			cmd = cmd->next;
			here_doc_check(cmd, HEREDOG);
			if (pipe(cmd->fd) == -1)
				perror("miniHell : pipe error");
			pid = fork();
			parent_or_child(pid, cmd, env, envp);
		}
		last_fd_close (cmd);
		while (wait(&g_exit_status) != -1)
			;
		g_exit_status = WEXITSTATUS(g_exit_status);
	}
	here_doc_check(cmd, UNLINK);
	reset_std_fd(cmd, head);
}
