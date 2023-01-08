/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:42:34 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/08 21:57:20 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_arg(char *str)
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
