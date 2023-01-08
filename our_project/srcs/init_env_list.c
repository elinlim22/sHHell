/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:06:25 by huipark           #+#    #+#             */
/*   Updated: 2023/01/09 01:15:04 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_key(char *line)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		dest[j] = line[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	*get_env_value(char *line)
{
	char	*dest;
	int		i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	dest = ft_strdup(line + (i + 1));
	if (!dest)
		exit (1);
	return (dest);
}

static void	newnode(t_env *head, int i)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	while (head->next != NULL)
		head = head->next;
	newnode->key = get_env_key(environ[i]);
	newnode->value = get_env_value(environ[i]);
	newnode->next = NULL;
	newnode->prev = head;
	head->next = newnode;
}

void	init_env(t_env *env)
{
	int	i;

	i = 0;
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	env->prev = NULL;
	while (environ[i])
		newnode(env, i++);
}
