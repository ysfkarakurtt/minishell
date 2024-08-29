/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:01 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:03 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	enviroments_added(char *envp, t_env **env, int *i)
{
	(*env)[*i].name = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
	if (!(*env)[*i].name)
		return (err_print(MALLOC_ERR), 1);
	(*env)[*i].value = ft_substr(envp, ft_strchr(envp, '=') - envp + 1,
			ft_strlen(envp) - (ft_strchr(envp, '=') - envp + 1));
	if (!(*env)[*i].value)
		return (err_print(MALLOC_ERR), 1);
	(*i)++;
	return (0);
}

static t_env	*get_env_pwd(char *pwdbuf)
{
	t_env	*env;

	env = (t_env *) ft_calloc(sizeof(t_env), 2);
	if (!env)
		return (err_print(MALLOC_ERR), NULL);
	env[0].name = ft_strdup("pwd");
	getcwd(pwdbuf, sizeof(pwdbuf));
	env[0].value = ft_strdup(pwdbuf);
	return (env);
}

t_env	*initializer_env(char	**envp)
{
	t_env	*env;
	int		k;
	char	buffer_pwd[1024];

	k = 0;
	if (!envp || !(*envp))
	{
		env = get_env_pwd(buffer_pwd);
		if (!env)
			return (NULL);
		return (env);
	}
	env = (t_env *)ft_calloc(sizeof(t_env), ft_strlen2(envp) + 1);
	if (!env)
		return (err_print(MALLOC_ERR), NULL);
	while (envp[k])
	{
		if (enviroments_added(envp[k], &env, &k))
			return (NULL);
	}
	env_update(env, "OLDPWD", "");
	return (env);
}
