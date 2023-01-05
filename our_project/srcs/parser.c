/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:42:34 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/05 17:44:47 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
처음에 검사해야하는것?
1. 따옴표가 닫혀있는지 (짝수개인지만 확인!! 위치는 확인필요)
2. 세미콜론(;), 더블파이프(||), &, 백슬래시(\),				있으면 안됨
*/

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






static char	*token_len(char *str, int type)
{
	int	len;

	len = 0;
	if (type == STR || type == RIGT || type == LEFT)
		while (str[len] != ' ' && ft_isalnum(str[len]))
			len++;
	else if (type == SINQ)
		while (str[len] != '\'')
			len++;
	else if (type == DOUQ)
		while (str[len] != '"')
			len++;
	return (ft_substr(str, 0, len));
}

char	*token(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == ' ')
			str++;
		else if (ft_isalnum(*str))
			return (token_len(str, STR));
		else if (*str == '"')
			return (token_len(str, DOUQ));
		else if (*str == '\'')
			return (token_len(str, SINQ));
		else if (*str == '|')
			return (ft_strdup("|"));
		else if (*str == '<' || *str == '>')
		 ////
}



// 			len = token_len(str, STR);
// 			str += len;
// 			return (ft_substr(str, 0, len));
// 		}
// 		else if (*str == '|')
// 		{
// 			str++;
// 			return (ft_strdup("|"));
// 		}
// 		else if (*str == '<')
// 		{
// 			if (*(str + 1) != '<')
// 			{
// 				len = token_len(str, STR);
// 				str += len;
// 				return (ft_substr(str, 0, len));
// 			}
// 			else
// 			{
// 				str++;
// 				continue ;
// 			}
// 		}
// 		else if (*str == '>')
// 		{
// 			if (*(str + 1) != '>')
// 			{
// 				len = token_len(str, STR);
// 				str += len;
// 				return (ft_substr(str, 0, len));
// 			}
// 			else
// 			{
// 				str++;
// 				continue ;
// 			}
// 		}
// 	}
// }
