/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:09 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:34:14 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_white_space(char x)
{
	if (x == 32 || x == 9 || x == 10 || x == 11 || x == 12 || x == 13)
	{
		return (1);
	}
	return (0);
}

static int	space_and_exit(char a, const char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '\0' || a != '\0')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str, int *flag)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	while (is_white_space(str[i]))
		i++;
	if (space_and_exit(str[i], str))
		*flag = 0;
	return (result * sign);
}
