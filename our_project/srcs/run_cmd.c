/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:58:35 by huipark           #+#    #+#             */
/*   Updated: 2023/01/11 22:08:28 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_handler(t_cmd *cmd)
{
	while (cmd->red)
		cmd->red = cmd->red->next;

}

void	do_parent(t_cmd *cmd, t_env env)
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

void	builtin_check(t_cmd *cmd, t_env env)
{
	if (!cmd->red && !cmd->tok && cmd->next)	//cmd가 헤드일 경우
		cmd = cmd->next;
	if (!cmd->next)
		do_parent(cmd, env);
	// else
	// 	do_child
}
