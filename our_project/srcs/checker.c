/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:42:34 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/06 14:04:47 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* initial checker */

static int	count_char(char *str, char q)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == q)
			count++;
	}
	return (count);
}

int	check_arg(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ';' || (str[i] == '|' && str[i + 1] == '|') \
		|| str[i] == '\\')
			return (0);
		else if (!(count_char(str, '"') % 2) || !(count_char(str, '\'') % 2))
			return (0);
	}
	return (1);
}
