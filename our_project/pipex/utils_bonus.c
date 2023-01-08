/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:12:01 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/13 19:19:45 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_cmd(char **cmd, char *argv, char **list);
void	get_path(t_pipex *all);
void	get_av(t_pipex *all, char *argv);
void	get_list(t_pipex *all, char **argv, int i);

void	get_cmd(char **cmd, char *argv, char **list)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!list || !*list)
		err_msg_fd("environ invalid", 2, 1);
	while (list[i])
	{
		tmp = ft_strdup(list[i]);
		if (!ft_strchr(argv, '/'))
			addstr(&tmp, argv);
		if (access(tmp, X_OK | F_OK) == 0)
		{
			*cmd = tmp;
			return ;
		}
		i++;
		free(tmp);
	}
	ft_putstr_fd(argv, 2);
	perror(": command not found");
}

void	get_path(t_pipex *all)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH", 4))
		{
			all->list_path = ft_split(environ[i] + 5, ':');
			i = 0;
			while (all->list_path[i])
				addstr(&(all->list_path[i++]), "/");
			return ;
		}
		i++;
	}
	err_msg_fd("PATH unavailable", 2, 1);
}

void	get_av(t_pipex *all, char *argv)
{
	int	len;

	len = 0;
	if (all->n_av)
	{
		len = ft_strlen_db(all->n_av);
		while (--len)
			free(all->n_av[len]);
		free(all->n_av[0]);
		free(all->n_av);
	}
	all->n_av = NULL;
	all->n_av = ft_split(argv, ' ');
	if (!all->n_av)
		err_msg("n_av split fail");
}

void	get_list(t_pipex *all, char **argv, int i)
{
	get_av(all, argv[i + all->hd]);
	get_cmd(&all->cmd, all->n_av[0], all->list_path);
	execve(all->cmd, all->n_av, environ);
}
