/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_pro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:42:42 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:44 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_env	*env_del(t_env *env, char *name)
{
	t_check	check;
	t_env	*new_env;

	check = init_check();
	check.name = name;
	new_env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen3(env));
	if (!new_env)
		return (err_print(MALLOC_ERR), NULL);
	while (env[check.i].name)
	{
		if (add_old_env_to_new_env_delete(env, new_env, &check))
			return (free_env(new_env), NULL);
	}
	free_env(env);
	return (new_env);
}

t_env	*env_update(t_env *env, char *name, char *value)
{
	int		k;
	char	*older_variable;

	k = 0;
	while (env[k].name)
	{
		if (!ft_strncmp(env[k].name, name, ft_strlen(name) + 1))
		{
			older_variable = env[k].value;
			env[k].value = ft_strdup(value);
			if (!env[k].value)
				return (env[k].value = older_variable,
					err_print(MALLOC_ERR), NULL);
			free(older_variable);
			return (env);
		}
		k++;
	}
	return (NULL);
}

char	*ft_strjoin_char(char *arr1, char a)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)ft_calloc(sizeof(char), ft_strlen(arr1) + 2);
	if (!result)
		return (free(arr1), err_print(MALLOC_ERR), NULL);
	while (arr1[i])
	{
		result[i] = arr1[i];
		i++;
	}
	result[i] = a;
	free(arr1);
	return (result);
}

char	*env_read(char *name, t_env *env)
{
	int	j;

	j = 0;
	while (env[j].name)
	{
		if (ft_strncmp(env[j].name, name, ft_strlen(name) + 1) == 0)
			return (env[j].value);
		j++;
	}
	return (NULL);
}

int	check_env(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(env[i].name, name, ft_strlen(name) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}
