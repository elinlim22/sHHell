/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:56:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 21:46:58 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*ready_to_run(char *str)
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
		run_export(cmd->next->tok->next, env);		//test
		while (!exit_check(str) && cmd->next)
		{
			cmd = cmd->next;
			printf("-----------------------------------------\n");
			printf("cmd node%d\n", i++);
			while (cmd->tok->next)
			{
				cmd->tok = cmd->tok->next;
				// if (!ft_strncmp(cmd->tok->str, "echo", 4))
				// 	say_it(cmd->tok);
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
		print_env(env);									//test
		free_cmd(cmd);
		add_history(str);
		free(str);
	}
}

// for (t_cmd *curr = cmd->next; curr->next; curr = curr->next)
// {
// 	for (t_tok *ttt = curr->tok->next; ttt->next; ttt = ttt->next)
// 		printf("[%s : %d] ", ttt->str, ttt->type);
// 	printf("\n");
// 	for (t_red *rrr = curr->red->next; rrr->next; rrr = rrr->next)
// 		printf("[%s : %d] ", rrr->str, rrr->type);
// 	printf("\n");
// }
