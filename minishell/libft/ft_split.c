/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:38:27 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	c_words(char const *s, char c)
{
	int	fl;
	int	i;
	int	w_count;

	i = 0;
	w_count = 0;
	fl = 1;
	while (s[i])
	{
		if (s[i] == c)
			fl = 1;
		else if (fl == 1 && s[i] != c)
		{
			w_count++;
			fl = 0;
		}
		i++;
	}
	return (w_count);
}

static char	**free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		word_index;

	if (!str)
		return (NULL);
	word_index = 0;
	result = (char **) malloc(sizeof(char *) * (c_words(str, c) + 1));
	if (!result)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			result[word_index] = malloc((word_len(str, c) + 1) * sizeof(char));
			if (!result[word_index])
				return (free_all(result));
			ft_strlcpy(result[word_index++], str, word_len(str, c) + 1);
			str += word_len(str, c);
		}
	}
	result[word_index] = NULL;
	return (result);
}
