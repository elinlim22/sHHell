/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:15 by huipark           #+#    #+#             */
/*   Updated: 2023/01/09 22:49:20 by huipark          ###   ########.fr       */
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

static void	print_env(t_env *copy_env)
{
	t_env	*temp;

	while (copy_env->prev)
		copy_env = copy_env->prev;
	while (copy_env->next)
	{
		copy_env = copy_env->next;
		if (!ft_strcmp(copy_env->key, "_"))
			continue;
		printf("declare -x ");
		printf("%s=\"%s\"\n", copy_env->key, copy_env->value);
	}
	while (copy_env->prev)
	{
		temp = copy_env->prev;
		free(copy_env);
		copy_env = temp;
	}
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

void	run_env(t_env env)
{
	t_env	*temp_env;
	t_env	*copy_env;

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
	print_env(copy_env);
}

int	main(void)
{
	t_env	env;

	init_env(&env);
	run_env(env);
}

// gcc -fsanitize=address libft.a builtin/env.c init_env_list.c
