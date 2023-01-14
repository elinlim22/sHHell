/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:13:21 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/14 14:18:33 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/* example(영민이꺼)
#include "../minishell.h"

extern t_global	g_minishell;

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[1] && argv[1][0] == '-')
	{
		ft_putendl_fd("pwd: options should not be included", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	pwd = getcwd(NULL, 0);
	if(!pwd)
	{
		perror("kiwishell: pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (EXIT_SUCCESS);
}
*/
