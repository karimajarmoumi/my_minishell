/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:46:29 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/23 15:44:13 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (((char *)s)[i] == (char)(c))
// 			break ;
// 		i++;
// 	}
// 	if (((char *)s)[i] == (char)(c))
// 		return ((char *)&s[i]);
// 	return (0);
// }

int ft_strchr_str(char *str, char *c)
{
	int	i;

	i = 0;
	if (str && c)
	{
		while (c[i])
		{
			if (ft_strchr(str, c[i]))
				return (1);
			i++;
		}
	}
	return (0);
}