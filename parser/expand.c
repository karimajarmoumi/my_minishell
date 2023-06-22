/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:29:23 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 23:06:55 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	expand(char **token)
{
	int		i;
	int		len;
	int		flag;
	char	*store;
	char	*result;

	i = 0;
	flag = 0;
	store = ft_strdup("");
	if (token && *token)
	{
		store_data_before_dollar(token, &store);
		len = ft_strlen(*token);
		if ((*token)[i] == '$')
		{
			while (i < len)
			{
				if ((*token)[i] && (*token)[i + 1] && (*token)[i] == '$'
					&& (*token)[i + 1] == '$')
				{
					i += 2;
					flag = 1;
				}
				else
				{
					check_dollar(*token, &store, &i, &flag);
					result = ft_strdup("");
					string_to_expand(*token, &i, &result);
					if (ft_strlen(result) > 1)
						expand_result(result, &flag, &store);
					else
						store_special_char(*token, &i, &result, &store);
				}
				result = NULL;
			}
			*token = store;
		}
	}
}
