/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:56 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:58 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal;

static int	requel(t_token **tokens, t_cmd ***commands)
{
	*tokens = appender(*tokens);
	if (!*tokens)
	{
		exit_variable_update(EXIT_SET, 1, 0);
		return (1);
	}
	*commands = parser(*tokens);
	if (*commands)
		free_tokens(tokens);
	if (!*commands)
	{
		exit_variable_update(EXIT_SET, 1, 0);
		return (1);
	}
	return (0);
}

static void	init_input(char *input, t_env **env)
{
	t_cmd	**commands;
	t_token	*tokens;

	g_signal = FT_SIGST;
	tokens = lexer(input);
	if (!tokens)
	{
		exit_variable_update(EXIT_SET, 1, 0);
		return ;
	}
	tokens = expander(tokens, *env);
	if (!tokens)
	{
		exit_variable_update(EXIT_SET, 1, 0);
		return ;
	}
	if (requel(&tokens, &commands))
		return ;
	execute_commands(commands, env);
	free_commands(commands);
}

void	input_read(t_env **env)
{
	char	*new_inputs;

	while (1)
	{
		new_inputs = readline(PROMPT);
		if (!new_inputs)
		{
			printf("exit\n");
			free_env(*env);
			free(env);
			exit(exit_variable_update(EXIT_GET, 0, 0));
		}
		if (!*new_inputs)
		{
			free(new_inputs);
			continue ;
		}
		init_input(new_inputs, env);
		add_history(new_inputs);
		free(new_inputs);
	}
}

int	main(int argc, char **argv, char **environments)
{
	t_env	**env;
	int		exit_value;

	(void)argv;
	if (argc != 1)
		return (err_print("Please type only one arguments"), 1);
	exit_variable_update(EXIT_FIRST, 0, &exit_value);
	env = malloc(sizeof(t_env *));
	if (!env)
		return (err_print(MALLOC_ERR), 1);
	*env = initializer_env(environments);
	if (!*env)
		return (free(env), 1);
	printf("\033[1;31mMinishell");
	printf("\033[0m by \033[35mmportaka\033[0m & \033[32mykarakur\033[0m\n");
	printf("\n");
	sig_controller();
	input_read(env);
	return (0);
}
