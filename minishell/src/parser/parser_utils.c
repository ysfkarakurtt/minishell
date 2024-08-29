/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:03 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:05 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	count_pipe(t_token *tokens)
{
	int	number;
	int	k;

	number = 0;
	k = 0;
	while (tokens[k].content)
	{
		if (tokens[k].type == PIPE)
			number++;
		k++;
	}
	return (number);
}

t_check	init_check(void)
{
	t_check	check;

	check.i = 0;
	check.k = 0;
	check.j = 0;
	check.fd_in = 0;
	check.fd_out = 1;
	check.is_command = 1;
	check.status = 0;
	check.check_flag = 1;
	return (check);
}

t_cmd	**init_commands(t_token *tokens, t_check check)
{
	t_cmd	**commands;

	commands = (t_cmd **)ft_calloc(sizeof(t_cmd *), count_pipe(tokens) + 2);
	if (!commands)
		return (err_print(MALLOC_ERR),
			free_tokens(&tokens), NULL);
	while (check.i < count_pipe(tokens) + 1)
	{
		commands[check.i] = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
		if (!commands[check.i])
			return (err_print(MALLOC_ERR),
				free_commands(commands), free_tokens(&tokens), NULL);
		check.i++;
	}
	check.i = 0;
	return (commands);
}
