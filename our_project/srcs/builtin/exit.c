/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:07:58 by huipark           #+#    #+#             */
/*   Updated: 2023/01/10 16:21:58 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *msg, int status)
{
	printf("%s\n", msg);
	exit(status);
}

void	exit_argm_check(char *msg, char *argm, int status)
{
	printf("%s%s:  numeric argument required\n", msg, argm);
	exit(status);
}

static int	exit_final_check(char *num, char *str)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			exit_argm_check("miniHell: exit: ", num, 255);
		i++;
	}
	while (*str)
	{
		if (ft_isalnum(*str))
		{
			printf("miniHell: too many arguments\n");
			return (1);
		}
		str++;
	}
	i = ft_atoi(num);
	ft_exit("Dobby is free!!", i);
	return (0);
}

int	exit_check(char *str)
{
	int		i;
	char	*num;

	num = NULL;
	while (*str == ' ')
		str++;
	i = 0;
	if (ft_strcmp(str, "exit") == 0)
		ft_exit("Dobby is free!!", EXIT_SUCCESS);
	else if (ft_strncmp(str, "exit", 4) == 0 && str[4] == ' ')
	{
		str += 4;
		while (*str == ' ')
			str++;
		if (*str == '-' || *str == '+')
			i++;
		while (str[i] != ' ' && str[i])
			i++;
	}
	else
		return (0);
	num = ft_substr(str, 0, i);
	str += i + 1;
	exit(exit_final_check(num, str));
}
