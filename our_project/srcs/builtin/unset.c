/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:23:47 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 02:16:22 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_argm_check(t_tok *tok, int *flag)
{
	int	i;

	i = 0;
	if (!ft_isalpha(tok->str[i]) && tok->str[i] != '_')
	{
		printf("miniHHell: unset: `%s': not a valid identifier\n", tok->str);
		*flag = 1;
		return (EXIT_FAILURE);
	}
	i++;
	while (tok->str[i])
	{
		if (!ft_isalnum(tok->str[i]) && tok->str[i] != '_')
		{
			printf("miniHHell: unset: `%s': not a valid identifier\n",
				tok->str);
			*flag = 1;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	search_env_key(t_tok **tok, t_env **env, t_env *head)
{
	if (!ft_strcmp((*tok)->str, (*env)->key)
		&& !(*(*tok)->str == '_' && *((*tok)->str + 1) == '\0'))
	{
		double_free((*env)->key, (*env)->value);
		if (!(*env)->next)
			(*env)->prev->next = NULL;
		else
		{
			(*env)->prev->next = (*env)->next;
			(*env)->next->prev = (*env)->prev;
		}
		free((*env));
		(*env) = head;
		(*tok) = (*tok)->next;
	}
}

int	run_unset(t_tok *tok, t_env *env)
{
	t_env	*head;
	int		flag;

	head = env;
	tok = tok->next;
	flag = 0;
	while (env->next && tok)
	{
		env = env->next;
		if (!unset_argm_check(tok, &flag))
			search_env_key(&tok, &env, head);
		else
		{
			tok = tok->next;
			env = head;
		}
	}
	if (flag == 1)
	{
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}
