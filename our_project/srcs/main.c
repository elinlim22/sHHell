/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:56:32 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/06 17:52:32 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *str;
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
			t_tok *tok = tokenize(str);
			t_red *red = init_red(tok);
			printf("------tester------\n");
			t_tok *curr;
			curr = tok->next;
			while (curr->next)
			{
				printf("[%s] : type = %d\n", curr->str, curr->type);
				curr = curr->next;
			}
			printf("[%s] : type = %d\n", curr->str, curr->type);
			printf("\n\n\n");
			while (red->next)
			{
				printf("red = [%s] : type = %d\n", red->str, red->type);
				red = red->next;
			}
			printf("red = [%s] : type = %d\n", red->str, red->type);
			printf("\n------------------\n");


		}
		add_history(str);
		free(str);
	}
}


// void	prompt()
// {
// 	char *str;
// 	while (1)
// 	{
// 		str = readline("\033[0;35mminihell $ \033[0m");
// 		if (ft_strncmp(str, "exit", 4) == 0)
// 		{
// 			printf("exit!!\n");
// 			break ;
// 		}
// 		else
// 			printf("res : %s\n", str);
// 		add_history(str);
// 		free(str);
// 	}
// }



// int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
// {
// 	t_env	env;
// 	t_cmd	*cmd;


// 	init_env(&env, envp);
// 	prompt();
// 	while (1)
// 	{
// 		cmd = init_cmd_list();
// 	}


// }








// char *single_split(char **input)
// {
// 	char	*dest;
// 	int		i;
// 	int		space

// 	i = 0;
// 	space = 0;
// 	while (*input[space] == ' ')
// 		space++;
// 	*input += space + 1;
// 	while (*input[i] && *input != '|' && *input != '<' && *input != '>')      //등등
// 		i++;
// 	dest = ft_substr(*input, 0, i + 1);
// 	*input += i + 1;
// 	return (dest);
// }

// int	search_type(char *str)
// {
// 	while (*str)
// 	{
// 		if ()
// 	}
// }
