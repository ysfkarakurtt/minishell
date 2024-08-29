/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:48 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:44:50 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

char	**add_flag(char **flags, char *flag)
{
	char	**new_flags;
	int		i;

	i = 0;
	while (flags && flags[i])
		i++;
	new_flags = malloc(sizeof(char *) * (i + 2));
	if (!new_flags)
		return (NULL);
	i = 0;
	while (flags && flags[i])
	{
		new_flags[i] = flags[i];
		i++;
	}
	new_flags[i] = ft_strdup(flag);
	if (!new_flags[i])
	{
		free(new_flags);
		return (NULL);
	}
	new_flags[i + 1] = NULL;
	if (flags)
		free(flags);
	return (new_flags);
}
