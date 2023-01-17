/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:51:57 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 22:48:44 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_signal(int signum);
void	fork_signal2(int signum);
void	signal_redisplay(void);
void	heredoc_signal(void);
void	heredoc_signal_sigint(int signal);

/* util */

void	fork_signal2(int signum)
{
	if (signum != SIGQUIT)
		return ;
	printf("Quit: 3\n");
	g_exit_status = 131;
	signal(SIGQUIT, SIG_IGN);
}

void	fork_signal(int signum)
{
	if (signum != SIGINT)
		return ;
	g_exit_status = 130;
	printf("^C\n");
	signal(SIGINT, SIG_IGN);
}

void	signal_redisplay(void)
{
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 1);
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, signal_sigterm);
}

void	heredoc_signal_sigint(int signal)
{
	(void)signal;
	g_exit_status = 1;
	printf("\n");
	exit(g_exit_status);
}
