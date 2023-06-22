/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:38 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 03:16:46 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

char	**token_cmd_to_args(t_token *token_cmd)
{
	int		i;
	char	**tab;
	t_token	*tmp;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_lstsize_token(token_cmd) + 1));
	if (token_cmd)
	{
		tmp = token_cmd;
		if (tab)
		{
			while (tmp)
			{
				if (tmp->e_type != 4)
					tab[i++] = ft_strdup(tmp->value);
				tmp = tmp->next;
			}
			tab[i] = NULL;
		}
	}
	else
		tab[0] = NULL;
	return (tab);
}

char	*tokens_cmd_to_string(t_token *token)
{
	char	*buffer;
	char	*to_free;
	char	*store;

	if (token)
	{
		buffer = ft_strdup("");
		while (token)
		{
			to_free = buffer;
			buffer = ft_strjoin(buffer, token->value);
			function_free((void **)&to_free, 1);
			token = token->next;
		}
		return (store = ft_strjoin(buffer, "\0")
			, function_free((void **)&buffer, 1), store);
	}
	return (NULL);
}
