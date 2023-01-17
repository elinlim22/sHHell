/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:23:47 by huipark           #+#    #+#             */
/*   Updated: 2023/01/17 20:50:09 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_argm_check(t_tok *tok)
{
	int	i;

	while (tok->next)
	{
		i = 0;
		tok = tok->next;
		if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
		{
			printf("miniHHell: unset: `%s': not a valid identifier\n", tok->str);
			return (EXIT_FAILURE);
		}
		i++;
		while (tok->str[i])
		{
			if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_')
			{
				printf("miniHHell: unset: `%s': not a valid identifier\n",
					tok->str);
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	run_unset(t_tok *tok, t_env *env)
{
	t_env	*head;

	head = env;
	if (unset_argm_check(tok))
		return (EXIT_FAILURE);
	while (env->next && tok->next)
	{
		env = env->next;
		if (!ft_strcmp(tok->next->str, env->key)
			&& !(*tok->next->str == '_' && *(tok->next->str + 1) == '\0'))
		{
			double_free(env->key, env->value);
			if (!env->next)
				env->prev->next = NULL;
			else
			{
				env->prev->next = env->next;
				env->next->prev = env->prev;
			}
			free(env);
			tok = tok->next;
			env = head;
		}
	}
	return (EXIT_SUCCESS);
}
