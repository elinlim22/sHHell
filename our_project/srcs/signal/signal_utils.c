/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 22:25:30 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal_sigint(int signal);
void	signal_sigint(int signal);
void	child_signal_sigquit(int signal);
void	child_signal_sigterm(int signal);
void	signal_sigterm(int signal);

/* signal handling funcs */
void	child_signal_sigint(int signal)
{
	(void)signal;
	exit(g_exit_status);
	// printf("\b\b^C\n");
}

void	signal_sigint(int signal)
{
	(void)signal;
	g_exit_status = 1;
	printf("\n");
	signal_redisplay();
}

void	child_signal_sigquit(int signal)
{
	(void)signal;
	exit(g_exit_status);
	// printf("\b\b^\\Quit: 3\n");
}

void	child_signal_sigterm(int signal)
{
	(void)signal;
	g_exit_status = 0;
}

void	signal_sigterm(int signal)
{
	(void)signal;
	g_exit_status = 0;
	exit(g_exit_status);
}
