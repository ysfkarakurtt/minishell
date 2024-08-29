/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:05 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:07 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	if_end_dollar(char *string)
{
	int	k;

	k = 0;
	while (string[k])
	{
		if (string[k] == '$' && string[k + 1] == '\0')
			return (1);
		k++;
	}
	return (0);
}

t_token	*expander(t_token *tokens, t_env *env)
{
	char	*tmp;
	int		i;

	i = -1;
	while (tokens[++i].content)
	{
		if (tokens[i].type == DOUBLE_QUOTE || tokens[i].type == WORD)
		{
			if (!(i > 0 && ft_strncmp(tokens[i - 1].content, "<<", 3) == 0))
			{
				tmp = expander_env(env, tokens[i].content);
				if (!tmp)
					return (err_print(MALLOC_ERR), free_tokens(&tokens), NULL);
				if (if_end_dollar(tokens[i].content) == 1
					&& (tokens[i + 1].is_append == 0))
					tmp = ft_strjoin_char(tmp, '$');
				if (!tmp)
					return (err_print(MALLOC_ERR), free_tokens(&tokens), NULL);
				free(tokens[i].content);
				tokens[i].content = tmp;
			}
		}
	}
	return (tokens);
}
