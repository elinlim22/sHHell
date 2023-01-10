/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:33:16 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 15:01:38 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	all_n(char *str)
{
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	say_it(t_tok *tok)
{
	t_tok	*curr;
	int		n_flag;

	curr = tok->next;
	n_flag = 1;
	if (!ft_strncmp(curr->str, "-n", 2) && all_n(curr->str))
	{
		curr = curr->next;
		n_flag = 0;
	}
	while (curr)
	{
		printf("%s ", curr->str);
		curr = curr->next;
	}
	if (n_flag)
		printf("\n");
}

// static t_cmd	*ready_to_run(char *str)
// {
// 	t_cmd	*final;
// 	t_tok	*token;

// 	token = tokenize(str);
// 	final = chunk(&token);
// 	init_red(final);
// 	return (final);
// }

// int	main(void)
// {
// 	char	*str;
// 	t_cmd	*cmd;
// 	t_env	env;

// 	init_env(&env);
// 	while (1)
// 	{
// 		int	i = 1;
// 		str = readline("\033[0;35mminihell $> \033[0m");
// 		cmd = ready_to_run(str);
// 		while (!exit_check(str) && cmd->next)
// 		{
// 			cmd = cmd->next;
// 			printf("-----------------------------------------\n");
// 			printf("cmd node%d\n", i++);
// 			while (cmd->tok->next)
// 			{
// 				cmd->tok = cmd->tok->next;
// 				if (!ft_strncmp(cmd->tok->str, "echo", 4))
// 					say_it(cmd->tok);
// 				// printf("TOKEN = [%s : %d] ", cmd->tok->str, cmd->tok->type);
// 			}
// 			printf("\n");
// 			while (cmd->red->next)
// 			{
// 				cmd->red = cmd->red->next;
// 				// printf("RED = [%s : %d] ", cmd->red->str, cmd->red->type);
// 			}
// 			printf("\n-----------------------------------------\n\n\n");
// 		}
// 		free_cmd(cmd);
// 		add_history(str);
// 		free(str);
// 	}
// }

// //gcc -lreadline -fsanitize=address builtin/echo.c libft.a parsing/chunk.c builtin/exit.c free.c init_env_list.c parsing/init.c parsing/tokenizer.c parsing/iterator.c -o hyeslim
