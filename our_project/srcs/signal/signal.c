/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:00:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 18:38:28 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_status(void);
void	handle_signal_on_newline(void);
void	handle_signal_while_cmd(void);
void	signal_redisplay(void);
void	heredoc_signal(void);
void	heredoc_signal_sigint(int signal);

void	sig_status(void)
{
	pid_t			pid;
	int				status;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
		handle_signal_on_newline();
	else if (pid == 0)
		handle_signal_while_cmd();
}

/* 실행중일때 vs 빈 줄일때 */
void	handle_signal_on_newline(void)
{
	signal(SIGINT, signal_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, signal_sigterm);
}

void	handle_signal_while_cmd(void)
{
	signal(SIGINT, child_signal_sigint);
	signal(SIGQUIT, child_signal_sigquit);
	signal(SIGTERM, child_signal_sigterm);
}

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

// void	signal_sigint(int signal)
// {
// 	(void)signal;
// 	g_exit_status = 1;
// 	printf("\n");
// 	signal_redisplay();
// }

// void	heredoc_signal_sigquit(int signal)
// {
// 	(void)signal;
// 	g_exit_status = 131;
// 	printf("\b\b^\\Quit: 3\n");
// }

// void	heredoc_signal_sigterm(int signal)
// {
// 	(void)signal;
// 	g_exit_status = 0;
// }

// void	signal_sigterm(int signal)
// {
// 	(void)signal;
// 	g_exit_status = 0;
// 	exit(g_exit_status);
// }
