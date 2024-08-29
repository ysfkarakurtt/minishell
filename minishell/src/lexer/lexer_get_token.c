/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:11 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:14 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../header/minishell.h"

int	get_token_pipe(char *input, int *i, t_token **token)
{
	char	*token_str;

	if (input[*i] == '|')
	{
		token_str = ft_strdup("|");
		if (!token_str)
			return (err_print(MALLOC_ERR));
		*token = add_token(token, token_str, PIPE, isappend_pipe(input, i));
		if (!*token)
			return (err_print(MALLOC_ERR));
		(*i)++;
		return (1);
	}
	return (0);
}

int	get_token_bracket(char *input, int *i, t_token **token)
{
	char	*token_str;

	if (input[*i] == '(')
	{
		token_str = ft_strdup("(");
		if (!token_str)
			return (err_print(MALLOC_ERR));
		*token = add_token(token, token_str, BRACKET_OPEN, 0);
		if (!*token)
			return (err_print(MALLOC_ERR));
		(*i)++;
		return (1);
	}
	if (input[*i] == ')')
	{
		token_str = ft_strdup(")");
		if (!token_str)
			return (err_print(MALLOC_ERR));
		*token = add_token(token, token_str, BRACKET_CLOSE, 0);
		if (!*token)
			return (err_print(MALLOC_ERR));
		(*i)++;
		return (1);
	}
	return (0);
}

int	get_token_redirection(char *input, int *i, t_token **token)
{
	char	*token_str;
	int		len;

	len = 0;
	while (ft_isdigit(input[*i + len]))
		len++;
	if (input[*i + len] == '<' || input[*i + len] == '>')
	{
		if (input[*i + len + 1] == '<' || input[*i + len + 1] == '>')
			len++;
		len++;
		token_str = ft_substr(input, *i, len);
		if (!token_str)
			return (err_print(MALLOC_ERR));
		if (input[*i + len - 1] == '>')
			*token = add_token(token, token_str, RDR_OUT, 0);
		else if (input[*i + len - 1] == '<')
			*token = add_token(token, token_str, RDR_IN, 0);
		if (!*token)
			return (err_print(MALLOC_ERR));
		(*i) += len;
		return (1);
	}
	return (0);
}

static int	quote_token_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr("\'\"", str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
		return (err_print(QUOTE_ERR));
	return (i + 1);
}

int	get_token_quote(char *input, int *i, t_token **token)
{
	char	*token_str;
	int		len;

	len = quote_token_len(input + *i);
	if (len == FAILURE)
		return (FAILURE);
	if (len > 0)
	{
		token_str = ft_substr(input, *i + 1, len - 2);
		if (!token_str)
			return (err_print(MALLOC_ERR));
		if (input[*i] == '\'')
			*token = add_token(token, token_str, SINGLE_QUOTE,
					isappend_control(input, i));
		else if (input[*i] == '\"')
			*token = add_token(token, token_str, DOUBLE_QUOTE,
					isappend_control(input, i));
		if (!*token)
			return (err_print(MALLOC_ERR));
		(*i) += len;
		return (1);
	}
	return (0);
}
