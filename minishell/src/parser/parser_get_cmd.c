/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:44:58 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:00 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

void	print_syntax_error(char *str)
{
	printf("\033[31mminishell:\033[0m");
	printf(" syntax error near unexpected token `%s'\n", str);
}

int	add_flag_and_content(t_cmd **commands, t_token *tokens, t_check *check)
{
	if (check->check_flag && tokens[check->i].content[0] == '-')
	{
		commands[check->k]->flags_array = \
			add_flag(commands[check->k]->flags_array, tokens[check->i].content);
		if (!commands[check->k]->flags_array)
			return (err_print(MALLOC_ERR), free_commands(commands),
				free_tokens(&tokens), FAILURE);
	}
	else
	{
		commands[check->k]->content = \
			add_content(&commands[check->k]->content,
				ft_strdup(tokens[check->i].content), tokens[check->i].type,
				tokens[check->i].is_append);
		if (!commands[check->k]->content)
			return (err_print(MALLOC_ERR), free_commands(commands),
				free_tokens(&tokens), FAILURE);
		check->check_flag = 0;
	}
	return (1);
}

int	get_cmd_word(t_cmd **commands, t_token *tokens, t_check *check)
{
	if (check->is_command)
	{
		commands[check->k]->command = ft_strdup(tokens[check->i].content);
		if (!commands[check->k]->command)
			return (err_print(MALLOC_ERR),
				free_commands(commands), free_tokens(&tokens), FAILURE);
		check->is_command = 0;
	}
	else
	{
		if (add_flag_and_content(commands, tokens, check) == FAILURE)
			return (FAILURE);
	}
	return (1);
}

int	get_cmd_redir_in(t_cmd **commands, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (err_print(
				"syntax error near unexpected token `newline'"),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (tokens[check->i + 1].type == RDR_IN || tokens[check->i + 1].type
		== RDR_OUT || tokens[check->i + 1].type == PIPE)
		return (print_syntax_error(tokens[check->i + 1].content),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (ft_strncmp(tokens[check->i].content, "<<", 3) == 0)
		commands[check->k]->input_file = \
				add_file(&commands[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, "<", 2) == 0)
		commands[check->k]->input_file = \
				add_file(&commands[check->k]->input_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (err_print(
				"syntax error near unexpected token `<'"),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (!commands[check->k]->input_file)
		return (err_print(MALLOC_ERR), free_commands(commands),
			free_tokens(&tokens), FAILURE);
	check->i++;
	return (0);
}

int	get_cmd_redir_out(t_cmd **commands, t_token *tokens, t_check *check)
{
	if (!tokens[check->i + 1].content)
		return (err_print(
				"syntax error near unexpected token `newline'"),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (tokens[check->i + 1].type == RDR_IN || tokens[check->i + 1].type
		== RDR_OUT || tokens[check->i + 1].type == PIPE)
		return (print_syntax_error(tokens[check->i + 1].content),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (ft_strncmp(tokens[check->i].content, ">>", 3) == 0)
		commands[check->k]->output_file = \
				add_file(&commands[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 1);
	else if (ft_strncmp(tokens[check->i].content, ">", 2) == 0)
		commands[check->k]->output_file = \
				add_file(&commands[check->k]->output_file,
				ft_strdup(tokens[check->i + 1].content), 0);
	else
		return (err_print(
				"syntax error near unexpected token `>'"),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	if (!commands[check->k]->output_file)
		return (err_print(MALLOC_ERR),
			free_commands(commands), free_tokens(&tokens), FAILURE);
	check->i++;
	return (0);
}
