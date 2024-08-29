/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:39:44 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:39:47 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*lastpos;
	int		i;

	lastpos = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			lastpos = (char *)&s[i];
		i++;
	}
	if ((char) c == s[i])
		return ((char *)&s[i]);
	return (lastpos);
}
