/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:15 by huipark           #+#    #+#             */
/*   Updated: 2023/01/17 20:49:05 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env(t_tok *tok, t_env env)
{
	if (!tok->next)
	{
		while (env.next)
		{
			env = (*env.next);
			if (env.value)
				printf("%s=%s\n", env.key, env.value);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("env: %s: No such file or directory\n", tok->next->str);
		return (EXIT_FAILURE);
	}
}

t_env	*find_env(t_env *env, char *path, int key_or_value)
{
	t_env	*curr;

	curr = env->next;
	while (curr)
	{
		if (key_or_value == KEY)
		{
			if (!ft_strcmp(curr->key, path))
				return (curr);
		}
		else if (key_or_value == VALUE)
		{
			if (!ft_strnstr(curr->value, path, ft_strlen(path)))
				return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}
