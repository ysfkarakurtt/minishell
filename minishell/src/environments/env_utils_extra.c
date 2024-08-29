/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:42:36 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:39 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	ft_strlen3(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
		i++;
	return (i);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		free(env[i].name);
		if (env[i].value)
			free(env[i].value);
		i++;
	}
	free(env);
}

int	add_old_env_to_new_env(t_env *env, t_env *new_env, int *i)
{
	new_env[*i].name = ft_strdup(env[*i].name);
	if (!new_env[*i].name)
		return (err_print(MALLOC_ERR), 1);
	if (env[*i].value)
	{
		new_env[*i].value = ft_strdup(env[*i].value);
		if (!new_env[*i].value)
			return (err_print(MALLOC_ERR), 1);
	}
	else
		new_env[*i].value = 0;
	(*i)++;
	return (0);
}

t_env	*add_env(t_env *env, char *name, char *value)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen3(env) + 2);
	if (!new_env)
		return (err_print(MALLOC_ERR), NULL);
	while (env[i].name)
		if (add_old_env_to_new_env(env, new_env, &i))
			return (free_env(new_env), NULL);
	new_env[i].name = ft_strdup(name);
	if (!new_env[i].name)
		return (free_env(new_env), err_print(MALLOC_ERR), NULL);
	if (value)
	{
		new_env[i].value = ft_strdup(value);
		if (!new_env[i].value)
			return (free_env(new_env),
				err_print(MALLOC_ERR), NULL);
	}
	else
		new_env[i].value = 0;
	free_env(env);
	return (new_env);
}

int	add_old_env_to_new_env_delete(t_env *env, t_env *n_enw, t_check *check)
{
	if (ft_strncmp(env[check->i].name, check->name, ft_strlen(check->name) + 1))
	{
		n_enw[check->j].name = ft_strdup(env[check->i].name);
		if (!n_enw[check->j].name)
			return (err_print(MALLOC_ERR), 1);
		if (env[check->i].value)
		{
			n_enw[check->j].value = ft_strdup(env[check->i].value);
			if (!n_enw[check->j].value)
				return (err_print(MALLOC_ERR), 1);
		}
		else
			n_enw[check->j].value = 0;
	}
	else
		check->j--;
	check->i++;
	check->j++;
	return (0);
}
