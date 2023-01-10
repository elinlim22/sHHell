/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:02:23 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 21:55:06 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_dir(t_env *env, char *headto)
{
	if (chdir(headto))
	{
		if (access(headto, F_OK) == -1) ///
			printf("no such file or directory: ");
		else if (access(headto, X_OK) == -1)
			printf("permission denied: ");
		else
			printf("not a directory: ");
		printf(headto); ///
	}
	else
		change_dir(env, headto);
}

void	change_dir(t_env *env, char *headto)
{
	char	*old;
	t_env	*temp;

	old = getcwd(NULL, 0);
	temp = find_env(env, "PWD", KEY);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(headto);
	}
	temp = find_env(env, "OLDPWD", KEY);
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(old);
	}
	else
		set_oldpwd(env, headto);
	free(old);
}

void	set_oldpwd(t_env *env, char *path)
{
	t_env	*new;

	while (env->next)
		env = env->next;
	new = ft_wrap_malloc(sizeof(t_env));
	new->key = ft_strdup("OLDPWD");
	new->value = ft_strdup(path);
	new->next = NULL;
	new->prev = env;
	env->next = new;
}

int	cd(t_tok *tok, t_env *env) // cd 다음 토큰이 와야함
{
	t_env	*temp;
	t_tok	*path_tok;

	path_tok = tok;
	if (!path_tok)
	{
		temp = find_env(env, "HOME", KEY);
		if (!temp)
		{
			printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		check_dir(env, temp->value);
	}
	else
		check_dir(env, path_tok->str);
	return (EXIT_SUCCESS);
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
		// run_export(cmd->next->tok->next, env);		//test
		while (!exit_check(str) && cmd->next)
		{
			cmd = cmd->next;
			printf("-----------------------------------------\n");
			printf("cmd node%d\n", i++);
			if (!ft_strcmp(cmd->tok->next->str, "cd"))
				cd(cmd->tok->str, &env);
			while (cmd->tok->next)
			{
				cmd->tok = cmd->tok->next;
				if (!ft_strncmp(cmd->tok->str, "echo", 4))
					say_it(cmd->tok);
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
		// print_env(env);									//test
		free_cmd(cmd);
		add_history(str);
		free(str);
	}
}
/*
	cd $변수 일 때 변수 경로 찾아서 path 에 저장 후 이동
	cd $(없는 환경변수) 일 때 에러메세지 없이 ~로 이동
	cd (ㅇㅣㄴ자 2개)일 때 뒤에인자 무시
	unset후 이동할때 minishell: cd: HOME not set


	cd (인자 2개) 일 때 minishell: cd: (인자): No such file or directory
	cd, cd ~ 일 때 HOME경로 찾아서 path에 저장 후 이동
	cd ~ (인자) 일 때 에러메세지 없이 ~로 이동
*/
