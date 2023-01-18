/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:45:03 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 13:55:37 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmd(t_cmd *cmd)
{
	t_tok	*head;
	char	**temp;
	int		row;
	int		col;

	head = cmd->tok;
	col = 0;
	row = 0;
	while (cmd->tok->next)
	{
		cmd->tok = cmd->tok->next;
		col++;
	}
	temp = (char **)ft_wrap_malloc(sizeof(char *) * (col + 1));
	cmd->tok = head;
	while (cmd->tok->next)
	{
		cmd->tok = cmd->tok->next;
		temp[row++] = row_malloc(cmd->tok);
	}
	temp[row] = NULL;
	return (temp);
}

char	*get_vaild_cmd(char **path, char *cmd)
{
	int		i;
	char	*temp_address;
	char	*temp_path;
	char	*temp_cmd;

	i = 0;
	temp_path = NULL;
	if (!path)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	temp_cmd = ft_strjoin("/", cmd);
	if (!temp_cmd)
		exit (1);
	while (path[i])
	{
		temp_address = temp_path;
		temp_path = ft_strjoin(path[i], temp_cmd);
		free (temp_address);
		if (access(temp_path, X_OK) == 0)
			return (temp_path);
		i++;
	}
	return (cmd);
}

char	**get_path(t_env *env)
{
	int	i;

	i = 0;
	while (env->next)
	{
		env = env->next;
		if (!ft_strncmp(env->key, "PATH", 4))
			return (ft_split(env->value, ':'));
	}
	return (NULL);
}
