/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:13:21 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 22:13:22 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
