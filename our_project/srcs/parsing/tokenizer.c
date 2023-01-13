/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:04:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/13 16:08:132 by hyeslim          ###   ########.fr       */
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
// return (value->)
// }

// static void	sub_parsing(t_env *env, t_tok *tok)
// {
// 	char	*ptr;
// 	char	*path;

// 	ptr = tok->str;
// 	path = NULL;
// 	if (tok->type == DOUQ)
// 	{
// 		while (*ptr != '$')
// 			ptr++;
// 		path = replace_path(env, ptr);
// 	}
// 	else if (tok->type == STR)
// }

// void	check_dollar(t_env *env, t_tok *tok)
// {
// 	t_tok	*curr;

// 	curr = tok->next;
// 	while (curr)
// 	{
// 		if (ft_strchr(tok->str, '$')) //$가 있는 토큰
// 			sub_parsing(env, curr);
// 		curr = curr->next;
// 	}
// }
