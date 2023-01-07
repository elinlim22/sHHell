/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:56:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/07 21:16:17 by hyeslim          ###   ########.fr       */
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
	int	i = 1;

	while (1)
	{
		str = readline("\033[0;35mminihell $> \033[0m");
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			printf("Dobby is free!!\n");
			break ;
		}
		else
		{
			cmd = ready_to_run(str);
			// for (t_cmd *curr = cmd->next; curr->next; curr = curr->next)
			// {
			// 	for (t_tok *ttt = curr->tok->next; ttt->next; ttt = ttt->next)
			// 		printf("[%s : %d] ", ttt->str, ttt->type);
			// 	printf("\n");
			// 	for (t_red *rrr = curr->red->next; rrr->next; rrr = rrr->next)
			// 		printf("[%s : %d] ", rrr->str, rrr->type);
			// 	printf("\n");
			// }
			while (cmd->next)
			{
				cmd = cmd->next;
				printf("cmd node%d\n", i++);
				while (cmd->tok->next)
				{
					cmd->tok = cmd->tok->next;
					printf("[%s : %d] ", cmd->tok->str, cmd->tok->type);
				}
				printf("\n");
				while (cmd->red->next)
				{
					cmd->red = cmd->red->next;
					printf("[%s : %d] ", cmd->red->str, cmd->red->type);
				}
				printf("\n");
			}
		}
		add_history(str);
		free(str);
		free_cmd(cmd);
	}
}
