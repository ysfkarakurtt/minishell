/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:42:52 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:55 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	is_env_variable_char(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static int	get_exit_value(char **tmp2, char **tmp, char **res)
{
	*tmp2 = ft_itoa(exit_variable_update(EXIT_GET, 0, 0));
	if (!tmp2)
		return (free(*res),
			err_print(MALLOC_ERR), FAILURE);
	*tmp = ft_strjoin(*res, *tmp2);
	if (!tmp)
		return (free(*res), free(*tmp2),
			err_print(MALLOC_ERR), FAILURE);
	free(*tmp2);
	return (0);
}

static int	get_dollar_content(t_check check, char **tmp2,
								char **tmp, char **res)
{
	*tmp2 = ft_substr(check.name, check.i + 1, check.j - 1);
	if (!*tmp2)
		return (free(*res),
			err_print(MALLOC_ERR), FAILURE);
	*tmp = ft_strjoin(*res, env_read(*tmp2, *check.env));
	if (!*tmp)
		return (free(*res), free(*tmp2),
			err_print(MALLOC_ERR), FAILURE);
	free(*tmp2);
	return (0);
}

int	expander_dollar(t_check *check, char **result, char **arr, char **arr2)
{
	check->j = 1;
	while (check->name[check->i + check->j]
		&& is_env_variable_char(check->name[check->i + check->j]))
		check->j++;
	if (check->name[check->i + check->j - 1] == '$'
		&& check->name [check->i + check->j++] == '?')
	{
		if (get_exit_value(arr2, arr, result) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (get_dollar_content(*check, arr2, arr, result) == FAILURE)
			return (FAILURE);
	}
	if (!*arr)
		return (err_print(MALLOC_ERR), FAILURE);
	free(*result);
	*result = *arr;
	check->i += check->j - 1;
	return (0);
}

char	*expander_env(t_env *env, char *name)
{
	char	*result;
	char	*arr;
	char	*arr2;
	t_check	check;

	check = init_check();
	check.name = name;
	check.env = &env;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (name[check.i])
	{
		if (name[check.i] != '$')
		{
			result = ft_strjoin_char(result, name[check.i]);
			if (!result)
				return (NULL);
		}
		else
			if (expander_dollar(&check, &result, &arr, &arr2) == FAILURE)
				return (NULL);
		check.i++;
	}
	return (result);
}
