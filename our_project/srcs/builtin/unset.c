/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:23:47 by huipark           #+#    #+#             */
/*   Updated: 2023/01/11 18:55:01 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_argm_check(t_tok *tok)
{
	int	i;

	while (tok->next)
	{
		i = 0;
		tok = tok->next;
		if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
		{
			printf("miniHHell: unset: `%s': not a valid identifier\n", tok->str);
			// g_exit_status = 1;
			return ;
		}
		i++;
		while (tok->str[i])
		{
			if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_')
			{
				printf("miniHHell: unset: `%s': not a valid identifier\n", tok->str);
				// g_exit_status = 1;
				return ;
			}
			i++;
		}
	}
}

void	run_unset(t_tok *tok, t_env *env)
{
	t_env	*temp_env;

	unset_argm_check(tok);
	env = env->next;
	while (env)
	{
		if (!ft_strcmp(tok->next->str, env->key))
		{
			temp_env = env->prev;
			free(env->key);
			free(env->value);
			if (!env->next)
				env->prev->next = NULL;
			else
			{
				env->prev->next = env->next;
				env->next->prev = env->prev;
			}
			free(env);
			tok = tok->next;
			env = temp_env;
		}
		env = env->next;
	}
	// g_exit_status = 0;
	return ;
}
