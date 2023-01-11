/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:07:58 by huipark           #+#    #+#             */
/*   Updated: 2023/01/11 17:20:48 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *msg, int status)
{
	printf("%s\n", msg);
	exit(status);
}

void	exit_argm_error(char *msg, char *argm, int status)
{
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

void	exit_check(t_tok *tok)
{
	int		exit_status;

	exit_status = 0;
	if (!ft_strcmp(tok->str, "exit") && !tok->next)
		ft_exit("Dobby is free!!", EXIT_SUCCESS);
	else if (!ft_strcmp(tok->str, "exit") && tok->next)
	{
		if (num_check(tok->next->str))
			exit_argm_error("miniHell: exit: ", tok->next->str, 255);
		else if (tok->next->next)
		{
			printf("miniHell: too many arguments\n");
			// g_exit_status = 1;
			return ;
		}
	}
	exit_status = ft_atoi(tok->next->str);
	exit(exit_status);
}
