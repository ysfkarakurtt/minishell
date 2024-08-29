/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:29 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:32 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../header/minishell.h"

static t_token	*get_tokens(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input && input[i])
	{
		if (check_tokens(input, &i, &tokens) == 1)
			break ;
		while (input[i] && ft_strchr(" \t\n", input[i]))
			i++;
	}
	if (input[i] != '\0')
	{
		free_tokens(&tokens);
		return (NULL);
	}
	return (tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(input);
	if (tokens && tokens[0].type == PIPE)
	{
		free_tokens(&tokens);
		err_print("syntax error near unexpected token `newline'");
		return (NULL);
	}
	return (tokens);
}

int	check_tokens(char *input, int *i, t_token **tokens)
{
	int	flag;

	flag = 0;
	if (get_token_pipe(input, i, tokens) == FAILURE)
		flag = 1;
	if (get_token_bracket(input, i, tokens) == FAILURE)
		flag = 1;
	if (get_token_redirection(input, i, tokens) == FAILURE)
		flag = 1;
	if (get_token_quote(input, i, tokens) == FAILURE)
		flag = 1;
	if (get_token_text(input, i, tokens) == FAILURE)
		flag = 1;
	return (flag);
}
