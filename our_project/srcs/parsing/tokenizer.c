/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:04:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/14 22:22:7 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*tokenize(char *str);

static int	token_cmd(t_tok **tok, char *str, int type)
{
	int		len;

	len = 0;
	if (type == STR)
		while (str[len] != ' ' && str[len])
			len++;
	else if (type == SINQ)
	{
		len++;
		while (str[len] != '\'')
			len++;
		len++;
	}
	else if (type == DOUQ)
	{
		len++;
		while (str[len] != '"')
			len++;
		len++;
	}
	add_tok(tok, ft_substr(str, 0, len), type);
	return (len);
}

static int	token_red(t_tok **tok, char *str)
{
	int		len;
	int		type;

	len = 0;
	type = 0;
	if (*(str + 1) == *str)
	{
		len = 2;
		if (*str == '<')
			type = DLFT;
		else
			type = DRGT;
	}
	else
	{
		len = 1;
		if (*str == '<')
			type = LEFT;
		else
			type = RIGT;
	}
	add_tok(tok, ft_substr(str, 0, len), type);
	return (len);
}

t_tok	*tokenize(char *str)
{
	t_tok	*tok;
	t_tok	*curr;

	tok = ft_wrap_malloc(sizeof(t_tok));
	init_tok(&tok);
	curr = tok;
	while (*str)
	{
		if (*str == '"')
			str += token_cmd(&curr, str, DOUQ);
		else if (*str == '\'')
			str += token_cmd(&curr, str, SINQ);
		else if (*str == '<' || *str == '>')
			str += token_red(&curr, str);
		else if (*str == ' ' || *str == '|')
		{
			if (*str == '|')
				add_tok(&curr, ft_strdup("|"), PIPE);
			str++;
		}
		else
			str += token_cmd(&curr, str, STR);
	}
	return (tok);
}

static char	*sub_parsing(t_env *env, t_tok *tok)
{
	char	*path;
	char	*str;
	char	*res;
	char	*temp;
	t_env	*env_temp;

	path = tok->str;
	str = NULL;
	res = ft_strdup("");
	temp = NULL;
	env_temp = NULL;
	while (*path && *path != '$')
		path++;
	path++;
	str = path;
	if (*str == '?')
	{
		free(res);
		res = ft_strdup(ft_itoa(g_exit_status));
	}
	else
	{
		while (*str && (*str != ' ' && *str != '!' && *str != '_' && *str != '&' && *str != '"'))
			str++;
		ft_strlcpy(&temp, path, str - path + 1);
		env_temp = find_env(env, temp, KEY);
		if (env_temp)
		{
			free(res);
			res = ft_strdup(env_temp->value);
		}
		// res = ft_strdup((find_env(env, temp, KEY))->value);
		free(temp);
		printf("str : %s\n", str);
		ft_addstr(&res, str);
	}
	// }
	// else if (tok->type == STR)
	// {
	// 	if (ft_strchr(tok->str, '?'))
	// 	{
	// 		res = ft_strdup(ft_itoa(g_exit_status));
	// 		ft_addstr(&res, (ft_strchr(tok->str, '?')) + 1);
	// 	}
	// 	else
	// 	{

	// 	}
	// 		res = ft_strdup((find_env(env, (tok->str + 1), KEY))->value);
	// }
	return (res);
}

void	check_dollar(t_env *env, t_tok *tok)
{
	t_tok	*curr;
	char	*temp;

	curr = tok->next;
	while (curr)
	{
		if (ft_strchr(curr->str, '$')) //$가 있는 토큰		//tok->str = 0x0
		{
			temp = sub_parsing(env, curr);
			free(curr->str);
			curr->str = temp;
		}
		curr = curr->next;
	}
}
