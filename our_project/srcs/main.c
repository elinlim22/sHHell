/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:56:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/11 22:08:27 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ready_to_run(char *str)
{
	t_cmd	*final;
	t_tok	*token;

	token = tokenize(str);
	final = chunk(&token);
	init_red(final);
	return (final);
}

void	argc_check(int argc, char *argv[])
{
	if (argc != 1)
	{
		printf("minihell: %s: no arguments required\n", argv[1]);
		exit (127);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_cmd	*cmd;
	t_env	env;

	argc_check(argc, argv);
	init_env(&env, envp);
	while (1)
	{
		int	i = 1;
		str = readline("\033[0;35mminihell $> \033[0m");
		if (!str)
			return (1);
		cmd = ready_to_run(str);
		builtin_check(cmd, env);
		while (cmd->next)
		{
			cmd = cmd->next;
			printf("-----------------------------------------\n");
			printf("cmd node%d\n", i++);
			while (cmd->tok->next)
			{
				cmd->tok = cmd->tok->next;
				printf("TOKEN = [%s : %d] ", cmd->tok->str, cmd->tok->type);
			}
			printf("\n");
			while (cmd->red->next)
			{
				cmd->red = cmd->red->next;
				printf("RED = [%s : %d] ", cmd->red->str, cmd->red->type);
			}
			printf("\n-----------------------------------------\n\n\n");
		}
		free_cmd(cmd);
		add_history(str);
		free(str);
	}
}
