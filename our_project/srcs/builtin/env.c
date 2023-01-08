/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:15 by huipark           #+#    #+#             */
/*   Updated: 2023/01/08 23:35:09 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_env(t_cmd *cmd, t_env env)
{
	/*  env 뒤에 인자가 있는경우 env: 인자내용: No such file or directory
		아직 실행부분을 구현하지 않아서 어떤식으로 매개변수와 인자가 올지몰라 보류
	if (cmd->tok->next->next->str != NULL)
	{
		exit_argm_check("env: ", cmd->tok->)
		exit(1);
	}
	*/
	while (env.next)
	{
		env = (*env.next);
		printf("%s=%s\n", env.key, env.value);
	}
	exit(0);
}
