/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:00 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:02 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	join_non_appendable_tokens(t_token *tokens, t_token **new_tokens, int i)
{
	char	*tmp;

	tmp = ft_strdup(tokens[i].content);
	if (!tmp)
		return (err_print(MALLOC_ERR),
			free_tokens(&tokens), 1);
	*new_tokens = add_token(new_tokens, tmp,
			tokens[i].type, tokens[i].is_append);
	if (!*new_tokens)
		return (err_print(MALLOC_ERR),
			free_tokens(&tokens), 1);
	return (0);
}

int	join_appendable_tokens(t_token *tokens, t_token **new_tokens, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	int		k;

	tmp = ft_strdup(tokens[i].content);
	if (!tmp)
		return (err_print(MALLOC_ERR),
			free_tokens(&tokens), 1);
	k = j;
	while (j > 0)
	{
		tmp2 = ft_strjoin(tmp, tokens[i + k - j + 1].content);
		if (!tmp2)
			return (err_print(MALLOC_ERR),
				free_tokens(&tokens), 1);
		free(tmp);
		tmp = tmp2;
		j--;
	}
	*new_tokens = add_token(new_tokens, tmp,
			tokens[i].type, tokens[i].is_append);
	if (!*new_tokens)
		return (err_print(MALLOC_ERR),
			free_tokens(&tokens), 1);
	return (0);
}

int	appender_continued(t_token *tokens, int *i, t_token **new_tokens)
{
	int	j;
	int	k;

	j = 0;
	while (tokens[*i + j + 1].is_append && (tokens[*i + j].type == WORD
			|| tokens[*i + j].type == SINGLE_QUOTE
			|| tokens[*i + j].type == DOUBLE_QUOTE))
		j++;
	k = j;
	if (j > 0)
	{
		if (join_appendable_tokens(tokens, new_tokens, *i, j))
			return (1);
	}
	else
		if (join_non_appendable_tokens(tokens, new_tokens, *i))
			return (1);
	*i += k + 1;
	return (0);
}

t_token	*appender(t_token *tokens)
{
	t_token	*new_tokens;
	int		i;

	i = 0;
	new_tokens = NULL;
	while (tokens[i].content)
		if (appender_continued(tokens, &i, &new_tokens))
			return (NULL);
	free_tokens(&tokens);
	return (new_tokens);
}
