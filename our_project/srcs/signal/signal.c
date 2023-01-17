/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:00:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/17 20:53:08 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_status(void);
void	handle_signal_on_newline(void);
void	handle_signal_while_cmd(void);

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
