/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:33 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:35 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>

void	cont_free(t_content **contents)
{
	int	i;

	i = 0;
	while ((*contents)[i].content)
	{
		free((*contents)[i].content);
		i++;
	}
	free(*contents);
}

void	free_commands(t_cmd **commands)
{
	int	a;

	a = 0;
	while (commands[a])
	{
		if (commands[a]->command)
			free(commands[a]->command);
		if (commands[a]->flags_array)
			free_double_char(commands[a]->flags_array);
		if (commands[a]->content)
			cont_free(&commands[a]->content);
		if (commands[a]->input_file)
			free_files(&commands[a]->input_file);
		if (commands[a]->output_file)
			free_files(&commands[a]->output_file);
		free(commands[a]);
		a++;
	}
	free(commands);
}

void	free_tokens(t_token **tokens)
{
	int	k;

	k = 0;
	while ((*tokens)[k].content && *tokens)
	{
		free((*tokens)[k].content);
		k++;
	}
	if (*tokens)
		free(*tokens);
}
