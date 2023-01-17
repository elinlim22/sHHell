/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:02:23 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 20:48:25 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dir(t_env *env, char *headto)
{
	if (chdir(headto))
	{
		if (access(headto, F_OK) == -1)
			printf("no such file or directory: ");
		else if (access(headto, X_OK) == -1)
			printf("permission denied: ");
		else
			printf("not a directory: ");
		printf("%s\n", headto);
		return (EXIT_FAILURE);
	}
	else
		change_dir(env, headto);
	return (EXIT_SUCCESS);
}

void	change_dir(t_env *env, char *headto)
{
	char	*old;
	t_env	*temp;

	old = getcwd(NULL, 0);
	temp = find_env(env, "PWD", KEY);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(headto);
	}
	temp = find_env(env, "OLDPWD", KEY);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(old);
	}
	else
		set_oldpwd(env, headto);
	free(old);
}

void	set_oldpwd(t_env *env, char *path)
{
	t_env	*new;

	while (env->next)
		env = env->next;
	new = ft_wrap_malloc(sizeof(t_env));
	new->key = ft_strdup("OLDPWD");
	new->value = ft_strdup(path);
	new->next = NULL;
	new->prev = env;
	env->next = new;
}

int	cd(t_tok *tok, t_env *env)
{
	t_env	*temp;
	t_tok	*path_tok;

	path_tok = tok;
	if (!path_tok || !ft_strcmp(path_tok->str, "~"))
	{
		temp = find_env(env, "HOME", KEY);
		if (!temp)
		{
			printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		if (check_dir(env, temp->value))
			return (EXIT_FAILURE);
	}
	else
	{
		if (check_dir(env, path_tok->str))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
