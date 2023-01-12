/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:34:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/12 16:31:222 by huipark          ###   ########.fr       */
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
	printf("child_signal_sigint\n");
	g_exit_status = 130;
	printf("\b\b\n^C");
	signal_redisplay();
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
	g_exit_status = 131;
	printf("\b\b\n^\\Quit: 3");
	signal_redisplay();
}

void	child_signal_sigterm(int signal)
{
	(void)signal;
	g_exit_status = 0;
	signal_redisplay();
}

void	signal_sigterm(int signal)
{
	(void)signal;
	g_exit_status = 0;
	exit(g_exit_status);
}
