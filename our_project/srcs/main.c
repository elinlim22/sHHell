/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:56:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/08 16:09:39 by huipark          ###   ########.fr       */
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

int	main(void)
{
	char *str;
	t_cmd *cmd;

	while (1)
	{
		int	i = 1;
		str = readline("\033[0;35mminihell $> \033[0m");
		if (!exit_check(str))
		{
			cmd = ready_to_run(str);
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
		}
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
