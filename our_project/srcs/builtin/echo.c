/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:16 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/08 23:35:33 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	all_n(char *str)
{
	while (*str)
	{
		if (*str != 'n')
			return (0);
	}
	return (1);
}

void	say_it(t_tok *tok)
{
	t_tok	*curr;
	int		n_flag;

	curr = tok->next;
	n_flag = 1;
	if (ft_strncmp(curr->str, "-n", 2) && all_n(curr->str + 2))
	{
		curr = curr->next;
		n_flag = 0;
	}
	while (curr)
	{
		ft_putstr_fd(curr->str, 2);
		curr = curr->next;
	}
	if (n_flag)
		ft_putchar_fd('\n', 2);
}

static t_cmd	*ready_to_run(char *str)
{
	t_cmd	*final;
	t_tok	*token;

	token = tokenize(str);
	final = chunk(&token);
	init_red(final);
	return (final);
}

int	main(void)
{
	char	*str;
	t_cmd	*cmd;
	t_env	env;

	init_env(&env);
	while (1)
	{
		// int	i = 1;
		str = readline("\033[0;35mminihell $> \033[0m");
		cmd = ready_to_run(str);
		while (!exit_check(str) && cmd->next)
		{
			cmd = cmd->next;
			if (ft_strncmp(str, "echo", 4))
				say_it(cmd->next->tok->next);
		}
		free_cmd(cmd);
		add_history(str);
		free(str);
	}
}

//gcc builtin/echo.c builtin/exit.c parsing/chunk.c free.c init_env_list.c parsing/init.c parsing/tokenizer.c parsing/iterator.c libft.a -lreadline
