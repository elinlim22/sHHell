/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:00:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/11 22:08:29 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_int(int signal) // 빈 줄일때 && ctrl-C
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_redisplay(int signal) // 빈 줄일때 ??
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal_on_newline(void)
{
	signal(SIGINT, signal_redisplay);
	signal(SIGQUIT, )
	signal(SIGTERM, exit);
}

void	handle_signal_while_cmd(void)
{
	signal(SIGINT, )
}


/* signal 처리
	실행중일때는 ^C 출력후 개행
	빈 라인에서는 그냥 개행
*/




/*
void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
*/
