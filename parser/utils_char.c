/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:43:16 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 03:13:49 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

int	pos_special_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (i);
		i++;
	}
	return (-1);
}

int	get_char_position(char *buffer, char c)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == c)
				return (i);
			i++;
		}
	}
	return (0);
}

char	*remove_char_from_str(char *buffer, char c)
{
	int		i;
	char	*str;
	char	*to_free;

	i = 0;
	str = ft_strdup("");
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] != c)
			{
				to_free = str;
				str = ft_strjoin(str, char_to_string(buffer[i]));
				function_free((void **)&str, 1);
			}
			i++;
		}
	}
	return (str);
}

int	ft_strchr_str(char *str, char *c)
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

int	len_str_to_expand(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			count++;
		i++;
	}
	return (count + 1);
}
