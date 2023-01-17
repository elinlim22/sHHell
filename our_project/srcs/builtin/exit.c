/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:07:58 by huipark           #+#    #+#             */
/*   Updated: 2023/01/17 16:34:03 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *msg, int status)
{
	printf("%s\n", msg);
	exit(status);
}

void	exit_argm_error(char *msg, char *argm, int status, t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	dup2(cmd->stdout_fd, STDOUT_FILENO);
	printf("%s%s:  numeric argument required\n", msg, argm);
	exit(status);
}

int	num_check(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exit_check(t_tok *tok, t_cmd *cmd)
{
	int		exit_status;

	exit_status = 0;
	if (!ft_strcmp(tok->str, "exit") && !tok->next)
		ft_exit("Dobby is free!!", EXIT_SUCCESS);
	else if (!ft_strcmp(tok->str, "exit") && tok->next)
	{
		if (num_check(tok->next->str))
			exit_argm_error("miniHell: exit: ", tok->next->str, 255, cmd);
		else if (tok->next->next)
		{
			printf("miniHell: too many arguments\n");
			return (EXIT_FAILURE);
		}
	}
	exit_status = ft_atoi(tok->next->str);
	exit(exit_status);
}
