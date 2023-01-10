/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/10 21:27:30 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	value_swap(t_env *copy_env,t_env *temp_env)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = temp_env->key;
	temp_env->key = copy_env->key;
	copy_env->key = temp_key;
	temp_value = temp_env->value;
	temp_env->value = copy_env->value;
	copy_env->value = temp_value;
}

static void	newnode(t_env env, t_env *temp)
{
	t_env *newnode;

	while (temp->next)
		temp = temp->next;
	newnode = ft_wrap_malloc(sizeof(t_env));
	newnode->key = env.key;
	newnode->value = env.value;
	newnode->next = NULL;
	newnode->prev = temp;
	temp->next = newnode;
}

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
	// exit(0);
}

t_env	*env_copy(t_env env)
{
	t_env	*temp;

	temp = ft_wrap_malloc(sizeof(t_env));
	temp->key = NULL;
	temp->value = NULL;
	temp->prev = NULL;
	temp->next = NULL;
	while (env.next)
	{
		env = (*env.next);
		newnode(env, temp);
	}
	return (temp);
}

void	export_error(char *argm)
{
	printf("bash: export: `%s': not a valid identifier\n", argm);
	exit (1);
}

void	add_env(t_env *env, char *str)
{
	t_env	*newnode;

	newnode = ft_wrap_malloc(sizeof(t_env));
	while (env->next)
		env = env->next;
	newnode->key = get_env_key(str);
	newnode->value = get_env_value(str);
	newnode->next = NULL;
	newnode->prev = env;
	env->next = newnode;
}

void	export_argm_check(t_tok *tok, t_env env)
{
	int	i;


		i = 0;
		if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
		{
			printf("\n\n\n\n\n\n\n");
			export_error(tok->str);
		}
		if ((tok->str[i] == '_' && tok->str[i + 1] == '='
		&& tok->str[i + 2] == '\0'))
			exit(0);
		while (tok->str[i])
		{
			if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_'
				&& tok->str[i] != '=')
				export_error(tok->str);
			i++;
		}
		add_env(&env, tok->str);
	// exit(0);
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
	return (1);
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

// gcc -fsanitize=address libft.a builtin/export.c init_env_list.c
