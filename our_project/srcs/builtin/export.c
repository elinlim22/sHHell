/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/09 16:56:37 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	run_export(t_env env)
{
	t_env	*temp_env;
	t_env	*copy_env;
	t_env	*head;
	char	*temp_key;
	char	*temp_value;

	copy_env = env_copy(env);
	head = copy_env;
	while (copy_env->next->next)
	{
		copy_env = copy_env->next;
		temp_env = copy_env;
		printf("COPY = %s\n",  copy_env->key);
		while (temp_env->next)
		{
			temp_env = temp_env->next;
			if (ft_strcmp(copy_env->key, temp_env->key) > 0)
			{
				temp_key = temp_env->key;
				temp_env->key = copy_env->key;
				copy_env->key = temp_key;
				temp_value = temp_env->value;
				temp_env->value = copy_env->value;
				copy_env->value = temp_value;
			}
		}
	}
	copy_env = head;
	while (copy_env->next)
	{
		copy_env = copy_env->next;
		printf("BASH %s\n", copy_env->key);
	}
}

int	main(void)
{
	// char	*str;
	// t_cmd	*cmd;
	t_env	env;

	init_env(&env);
	run_export(env);
// 	printf("\n\n");
// 	while (env.next)
// 	{
// 		env = (*env.next);
// 		printf("BASH %s\n", env.key);
// 	}
// }
// gcc -fsanitize=address -g3 libft.a builtin/export.c init_env_list.c
/*
	strcmp로 검사
	a > b 양수
	a < b 음수
	a = b 0
	모두 검사하고 모든 리턴값이 음수일경우 피봇str이 가장 적은 ascil 문자를 가진 str
	양수가 있는경우 가장 큰 값을 가진 str이 가장 적은 ascil 문자를 가진 str
*/
}
