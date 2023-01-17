/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:51:57 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 20:53:13 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_redisplay(void);
void	heredoc_signal(void);
void	heredoc_signal_sigint(int signal);

/* util */
void	signal_redisplay(void)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
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
	exit(g_exit_status);
}
