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

void	ft_perror(char *file)
{
	printf("miniHell : %s: ", file);
	perror("");
}

void	reset_stdfd(t_cmd *cmd)
{
	dup2(cmd->STDOUT_FD, STDOUT_FILENO);
	close(cmd->STDOUT_FD);
	dup2(cmd->STDIN_FD, STDIN_FILENO);
	close(cmd->STDIN_FD);
}

char	*red_check(t_red *red)
{
	char	*stdin;

	stdin = NULL;
	if (red->type == LEFT)
			stdin = red->str;
	else if (red->type == RIGT)
	{
		red->out_fd = open(red->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (red->out_fd == -1)
			ft_perror(red->str);
	}
	return (stdin);
}

void	fd_handler(t_cmd *cmd)
{
	char	*stdin;

	stdin = NULL;
	while (cmd->red->next)
	{
		cmd->red = cmd->red->next;
		stdin = red_check(cmd->red);
	}
	if (stdin)
	{
		cmd->red->in_fd = open(stdin, O_RDONLY);
		if (cmd->red->in_fd == -1)
			ft_perror(stdin);
		dup2(cmd->red->in_fd, STDIN_FILENO);
		close(cmd->red->in_fd);
	}
	dup2(cmd->red->out_fd, STDOUT_FILENO);
	close(cmd->red->out_fd);
}

void	do_parent(t_cmd *cmd, t_env env)
{
	fd_handler(cmd);
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
			run_pwd();
		else if (!ft_strcmp(cmd->tok->next->str, "echo"))     //echo $? 시 전역변수 출력 근데 전역변수 사용하면 링크에러남 ㅠㅠ
			say_it(cmd->tok->next);
		else if (!ft_strcmp(cmd->tok->next->str, "cd"))
			cd(cmd->tok->next->next, &env);
	}
}

void	builtin_check(t_cmd *cmd, t_env env)
{
	t_cmd *head;

	head = cmd;
	if (!cmd->red && !cmd->tok && cmd->next)	//cmd가 헤드일 경우
		cmd = cmd->next;
	if (!cmd->next)
		do_parent(cmd, env);
	else
		execute()



	cmd = head;
	reset_stdfd(cmd);
	// else
	// 	do_child
}
