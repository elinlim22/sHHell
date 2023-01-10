/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:15 by huipark           #+#    #+#             */
/*   Updated: 2023/01/10 19:37:57 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env env)
{
	while (env.next)
	{
		env = (*env.next);
		if (env.value)
			printf("%s=%s\n", env.key, env.value);
	}
}

// char	*ft_getenv(t_env *env, char *pathname)
// {
// 	t_env	*curr;

// 	curr = env->next;
// 	while (curr)
// 	{
// 		if (!ft_strncmp(curr->key, pathname, ft_strlen(pathname)))
// 			return (curr->value);
// 		curr = curr->next;
// 	}
// 	return (NULL);
// }

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

// t_env	*find_key(t_env *env, char *pathname)
// {
// 	t_env	*curr;

// 	curr = env->next;
// 	while (curr)
// 	{
// 		if (ft_strnstr(curr->value, pathname, ft_strlen(pathname)))
// 			return (curr);
// 		curr = curr->next;
// 	}
// 	return (NULL);
// }
