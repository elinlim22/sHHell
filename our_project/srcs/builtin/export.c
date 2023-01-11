/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/11 21:52:01 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(t_env *copy_env)
{
	while (copy_env->prev)
		copy_env = copy_env->prev;
	while (copy_env->next)
	{
		copy_env = copy_env->next;
		if (!ft_strcmp(copy_env->key, "_"))
			continue;
		printf("declare -x ");
		printf("%s", copy_env->key);
		if (copy_env->value)
			printf("=\"%s\"\n", copy_env->value);
		else
			printf("\n");
	}
	free_export(copy_env);
}

void	export_argm_check(t_tok *tok, t_env env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", tok->str);
		// g_exit_status = 1;
		return ;
	}
	printf("%s\n", tok->str);
	if ((tok->str[i] == '_' && tok->str[i + 1] == '='
	&& tok->str[i + 2] == '\0'))
		exit(0);
	while (tok->str[i])
	{
		if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_'
			&& tok->str[i] != '=')
		{
			printf("bash: export: `%s': not a valid identifier\n", tok->str);
			// g_exit_status = 1;
			return ;
		}
		i++;
	}
	add_env(&env, tok->str);
}

int	cover_up_env(t_env *env, char *src)
{
	char	*str;

	str = get_env_value(src);
	if (str)
	{
		if (*str == '\0')
			return (0);
		free(env->value);
		env->value = str;
	}
	return (0);
}

static int	existent_check(t_tok *tok, t_env *env)
{
	int	i;
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
		if (!ft_strcmp(key, env->key))
			return(cover_up_env(env, tok->str));
	}
	env = head;
	export_argm_check(tok, *env);
	return (0);
}

void	run_export(t_tok *tok, t_env env)
{
	t_env	*temp_env;
	t_env	*copy_env;

	if (tok->next)
	{
		while (tok->next)
		{
			tok = tok->next;
			existent_check(tok, &env);
		}
	}
	else
	{
		copy_env = env_copy(env);
		while (copy_env->next->next)
		{
			copy_env = copy_env->next;
			temp_env = copy_env;
			while (temp_env->next)
			{
				temp_env = temp_env->next;
				if (ft_strcmp(copy_env->key, temp_env->key) > 0)
					value_swap(copy_env, temp_env);
			}
		}
		print_export(copy_env);
	}
}
