/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 00:58:33 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_export(t_env *copy_env)
{
	while (copy_env->prev)
		copy_env = copy_env->prev;
	while (copy_env->next)
	{
		copy_env = copy_env->next;
		if (!ft_strcmp(copy_env->key, "_"))
			continue ;
		printf("declare -x ");
		printf("%s", copy_env->key);
		if (copy_env->value)
			printf("=\"%s\"\n", copy_env->value);
		else
			printf("\n");
	}
	free_export(copy_env);
	return (EXIT_SUCCESS);
}

int	export_argm_check(t_tok *tok, t_env env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", tok->str);
		return (EXIT_FAILURE);
	}
	if (tok->str[i] == '_' && tok->str[i + 1] == '=')
		return (EXIT_SUCCESS);
	while (tok->str[i])
	{
		if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_'
			&& tok->str[i] != '=')
		{
			printf("bash: export: `%s': not a valid identifier\n", tok->str);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (add_env(&env, tok->str));
}

int	cover_up_env(t_env *env, char *src)
{
	char	*str;

	str = get_env_value(src);
	if (str)
	{
		free(env->value);
		env->value = str;
	}
	return (EXIT_SUCCESS);
}

static int	existent_check(t_tok *tok, t_env *env)
{
	int		i;
	char	*key;
	t_env	*head;

	head = env;
	i = 0;
	while (tok->str[i] && tok->str[i] != '=')
		i++;
	if (tok->str[i] == '\0')
		key = ft_strdup(tok->str);
	else
		key = ft_substr(tok->str, 0, i);
	while (env->next)
	{
		env = env->next;
		if (!ft_strcmp(key, env->key) && *key != '_')
		{
			free(key);
			return (cover_up_env(env, tok->str));
		}
	}
	env = head;
	free(key);
	return (export_argm_check(tok, *env));
}

int	run_export(t_tok *tok, t_env env)
{
	if (tok->next)
	{
		while (tok->next)
		{
			tok = tok->next;
			g_exit_status = existent_check(tok, &env);
		}
		return (g_exit_status);
	}
	else
		return (print_export(run_export2(&env)));
}
