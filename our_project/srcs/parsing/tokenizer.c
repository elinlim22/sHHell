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

// static char	*replace_path(t_env *env, char *ptr)
// {
// 	int	i;
// 	char	*path;
// 	t_env	*value;

// 	i = 0;
// 	ptr++;
// 	while (ptr[i] != ' ' || ptr[i] != '!' || ptr[i] != '_' || ptr[i] != '&')
// 		i++;
// 	path = ft_substr(ptr, 0, i);
// 	value = find_env(env, path, KEY);
// 	return ()
// }

static char	*sub_parsing(t_env *env, t_tok *tok)
{
	char	*path;
	char	*str;
	char	*res;
	char	*temp;

	path = tok->str;
	str = NULL;
	res = NULL;
	temp = NULL;
	if (tok->type == DOUQ)
	{
		while (*path && *path != '$')
			path++;
		path++;
		// temp = ft_strdup((path + 1));
		str = path + 1;
		if (*str == '?')
			res = ft_strdup(ft_itoa(g_exit_status));
		else
		{
			while (*str && (*str != ' ' || *str != '!' || *str != '_' || *str != '&'))
				str++;
			ft_strlcpy(temp, (path + 1), str - path);
			res = ft_strdup((find_env(env, temp, KEY))->value);
			free(temp);
			ft_addstr(&res, str);
		}
	}
	else if (tok->type == STR)
	{
		if (ft_strchr(tok->str, '?'))
		{
			res = ft_strdup(ft_itoa(g_exit_status));
			ft_addstr(&res, (ft_strchr(tok->str, '?')) + 1);
		}
		else
			res = ft_strdup((find_env(env, (tok->str + 1), KEY))->value);
	}
	return (res);
}

void	check_dollar(t_env *env, t_tok *tok)
{
	t_tok	*curr;

	curr = tok->next;
	while (curr)
	{
		if (ft_strchr(tok->str, '$')) //$가 있는 토큰		//tok->str = 0x0
		{
			free(tok->str);
			tok->str = sub_parsing(env, curr);
		}
		curr = curr->next;
	}
}
