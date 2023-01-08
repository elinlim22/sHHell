/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/09 01:15:14 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_export(t_env env)
{
	t_env	king_env;
	t_env	temp_env;
	t_env	reset;
	char	*pivot_str;

	while (env.next->next)
	{
		env = (*env.next);
		temp_env = (*env.next);
		king_env = env;
		pivot_str = env.key;
		while (temp_env.next)
		{

			// printf("king === %s\n", king_env.key);
			if (ft_strcmp(king_env.key, temp_env.next->key) > 0)
				king_env = (*temp_env.next);
			temp_env = (*temp_env.next);
		}
		printf("%s\n", king_env.key);
		if (king_env.next != NULL)
		{
			king_env.prev->next = king_env.next;
			king_env.next->prev = king_env.prev;
			king_env.next = NULL;
		}
	}
}

int	main(void)
{
	char	*str;
	t_cmd	*cmd;
	t_env	env;

	init_env(&env);
	run_export(env);
	while (env.next)
	{
		env = (*env.next);
		printf("BASH %s\n", env.key);

	}
}
// gcc libft.a builtin/export.c init_env_list.c
/*
	strcmp로 검사
	a > b 양수
	a < b 음수
	a = b 0
	모두 검사하고 모든 리턴값이 음수일경우 피봇str이 가장 적은 ascil 문자를 가진 str
	양수가 있는경우 가장 큰 값을 가진 str이 가장 적은 ascil 문자를 가진 str
*/
