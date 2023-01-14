/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:16 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/14 22:04:08 by huipark          ###   ########.fr       */
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
	if (!ft_strncmp(curr->str, "-n", 2) && all_n(curr->str))
	{
		curr = curr->next;
		n_flag = 0;
	}
	while (curr)
	{
		i = 0;
		while (curr->str[i] != '\0')
		{
			// if (curr->str[i] == '$' && curr->str[i + 1] == '?')
			// {
			// 	printf("%d", g_exit_status);
			// 	i += 2;
			// }
			if (curr->str[i] != '\0')
			{
				printf("%c", curr->str[i]);
				i++;
			}
		}
		curr = curr->next;
	}
	if (n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
