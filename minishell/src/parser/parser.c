/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:08 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:10 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	check_reset(t_check *check)
{
	check->check_flag = 1;
	check->is_command = 1;
	check->i++;
	check->j++;
}

static int	get_cmd(t_cmd **commands, t_token *tokens, t_check *check)
{
	if (tokens[check->i].type == WORD || tokens[check->i].type == SINGLE_QUOTE
		|| tokens[check->i].type == DOUBLE_QUOTE)
		return (get_cmd_word(commands, tokens, check));
	else if (tokens[check->i].type == RDR_IN)
		return (get_cmd_redir_in(commands, tokens, check));
	else if (tokens[check->i].type == RDR_OUT)
		return (get_cmd_redir_out(commands, tokens, check));
	return (1);
}

static int	requel_parser(t_token *tokens, t_cmd **commands, t_check *check)
{
	while (tokens[check->i].content)
	{
		if (tokens[check->i].type == PIPE)
		{
			if (tokens[check->i + 1].type == PIPE)
			{
				if (tokens[check->i + 1].is_append == 0)
					err_print("syntax error near unexpected token `|'");
				else if (tokens[check->i + 1].is_append == 1)
					err_print("'||' is not allowed");
				free_commands(commands);
				free_tokens(&tokens);
				return (1);
			}
			check_reset(check);
			break ;
		}
		if (get_cmd(commands, tokens, check) == FAILURE)
			return (1);
		check->i++;
	}
	return (0);
}

t_cmd	**parser(t_token *tokens)
{
	t_cmd	**commands;
	t_check	check;

	check = init_check();
	commands = init_commands(tokens, check);
	if (!commands)
		return (free_tokens(&tokens), NULL);
	while (check.k < count_pipe(tokens) + 1)
	{
		if (!tokens[check.i].content)
		{
			err_print("syntax error: incomplete pipe");
			free_commands(commands);
			free_tokens(&tokens);
			return (NULL);
		}
		if (requel_parser(tokens, commands, &check))
			return (NULL);
		check.k++;
	}
	return (commands);
}
