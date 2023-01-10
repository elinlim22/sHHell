/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:04:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/10 13:04:54 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	token_cmd(t_tok **tok, char *str, int type)
{
	int		len;

	len = 0;
	// if (type == STR)
	// 	while (str[len] != ' ' && ft_isalnum(str[len]))
	// 		len++;
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

	// tok = (t_tok *)malloc(sizeof(t_tok));
	tok = ft_wrap_malloc(sizeof(t_tok));
	init_tok(&tok);
	curr = tok;
	// if (!tok || !str)
	// 	return (NULL);
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

/*
		else if (ft_isalnum(*str))
			str += token_cmd(&curr, str, STR);
		else if (*str == '"')
			str += token_cmd(&curr, str, DOUQ);
		else if (*str == '\'')
			str += token_cmd(&curr, str, SINQ);
		else if (*str == '<' || *str == '>')
			str += token_red(&curr, str);
		else if (*str++ == '|')
			add_tok(&curr, ft_strdup("|"), PIPE);
			*/
