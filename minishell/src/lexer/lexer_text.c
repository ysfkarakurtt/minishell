/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:17 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:20 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../header/minishell.h"

int	isappend_pipe(char *input, int *i)
{
	if (*i == 0)
		return (0);
	if (input[*i - 1] == '|')
		return (1);
	else
		return (0);
}

static int	meta_char_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}

static int	text_token_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" \t\n", str[i]))
			break ;
		else if (meta_char_len(&str[i]) > 0)
			break ;
		else if (ft_strchr("\'\"", str[i]))
			break ;
		i++;
	}
	return (i);
}

int	isappend_control(char *input, int *i)
{
	if (*i == 0)
		return (0);
	return (ft_strchr(" \t|", input[*i - 1]) == NULL);
}

int	get_token_text(char *input, int *i, t_token **token)
{
	int		start;
	int		len;
	char	*token_str;

	len = text_token_len(&input[*i]);
	if (len > 0)
	{
		start = *i;
		token_str = ft_substr(input, start, len);
		if (!token_str)
			return (err_print(MALLOC_ERR));
		*token = add_token(token, token_str, WORD, isappend_control(input, i));
		*i = start + len;
		return (1);
	}
	return (0);
}
