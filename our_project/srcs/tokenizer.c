/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:04:03 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/06 16:45:27 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	token_cmd(t_tok **tok, char *str, int type);
static int	token_red(t_tok **tok, char *str);
static void	tok_add(t_tok **tok, char *str, int type);
t_tok		*tokenize(char *str);

/* tokenize */

static int	token_cmd(t_tok **tok, char *str, int type)
{
	int		len;

	len = 0;
	if (type == STR)
		while (str[len] != ' ' && ft_isalnum(str[len]))
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
	tok_add(tok, ft_substr(str, 0, len), type);
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
	tok_add(tok, ft_substr(str, 0, len), type);
	return (len);
}

static void	tok_add(t_tok **tok, char *str, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->next = NULL;
	(*tok)->next = new;
	(*tok) = (*tok)->next;
}

t_tok	*tokenize(char *str)
{
	t_tok	*tok;
	t_tok	*curr;

	tok = (t_tok *)malloc(sizeof(t_tok));
	curr = tok;
	if (!tok || !str)
		return (NULL);
	while (*str)
	{
		if (*str == ' ')
			str++;
		else if (ft_isalnum(*str))
			str += token_cmd(&curr, str, STR);
		else if (*str == '"')
			str += token_cmd(&curr, str, DOUQ);
		else if (*str == '\'')
			str += token_cmd(&curr, str, SINQ);
		else if (*str == '<' || *str == '>')
			str += token_red(&curr, str);
		else if (*str++ == '|')
			tok_add(&curr, ft_strdup("|"), PIPE);
	}
	return (tok);
}
