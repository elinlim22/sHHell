/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:16 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 22:51:30 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	all_n(char *str)
{
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	say_it(t_tok *tok)
{
	t_tok	*curr;
	int		n_flag;
	int		i;

	curr = tok->next;
	n_flag = 1;
	if (curr->str && !ft_strncmp(curr->str, "-n", 2) && all_n(curr->str))
	{
		curr = curr->next;
		n_flag = 0;
	}
	while (curr)
	{
		i = 0;
		while (curr->str && curr->str[i] != '\0')
		{
			if (curr->str[i] != '\0')
				ft_putchar_fd(curr->str[i++], STDOUT_FILENO);
		}
		ft_putchar_fd(' ', STDOUT_FILENO);
		curr = curr->next;
	}
	if (n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
