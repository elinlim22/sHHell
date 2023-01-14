/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:52:35 by huipark           #+#    #+#             */
/*   Updated: 2023/01/14 14:33:16 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_newnode(t_env env, t_env *temp)
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

void	value_swap(t_env *copy_env,t_env *temp_env)
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
		env_newnode(env, temp);
	}
	return (temp);
}

int	add_env(t_env *env, char *str)
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
	return (EXIT_SUCCESS);
}
