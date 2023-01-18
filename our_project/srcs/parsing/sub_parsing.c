/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:25:51 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/18 01:23:41 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*is_questionmark(char **str, char **res)
{
	char	*temp;
	char	*num;

	num = ft_itoa(g_exit_status);
	ft_addstr(res, num);
	free (num);
	temp = ft_strdup("?");
	(*str)++;
	return (temp);
}

static void	replace_env_var(t_env *env, char **res, char *path)
{
	char	*str;
	t_env	*env_temp;
	char	*temp;

	str = path;
	temp = NULL;
	if (*str == '?')
		temp = is_questionmark(&str, res);
	else
	{
		while (*str && (*str != ' ' && *str != '!' \
			&& *str != '_' && *str != '&'))
			str++;
		ft_strlcpy(&temp, path, str - path + 1);
	}
	env_temp = find_env(env, temp, KEY);
	if (env_temp)
		ft_addstr(res, env_temp->value);
	free(temp);
	ft_addstr(res, str);
}

static char	*sub_parsing(t_env *env, t_tok *tok)
{
	char	*path;
	char	*res;

	path = tok->str;
	res = NULL;
	while (*path && *path != '$')
		path++;
	if (tok->str != path)
		ft_strlcpy(&res, tok->str, path - tok->str + 1);
	path++;
	replace_env_var(env, &res, path);
	return (res);
}

void	check_dollar(t_env *env, t_tok *tok)
{
	t_tok	*curr;
	char	*temp;

	curr = tok->next;
	while (curr)
	{
		if (ft_strchr(curr->str, '$')
			&& (curr->type == DOUQ || curr->type == STR))
		{
			temp = sub_parsing(env, curr);
			free(curr->str);
			curr->str = temp;
		}
		curr = curr->next;
	}
}
