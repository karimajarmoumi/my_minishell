/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:09:38 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/20 16:10:25 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

char	**token_cmd_to_args(t_token *token_cmd)
{
	t_token 	*tmp;
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_lstsize_token(token_cmd) + 1));
	if (token_cmd)
	{
		tmp = token_cmd;
		if (tab)
		{
			while (tmp)
			{
				if (tmp->type != 4)
				{
					tab[i] = ft_strdup(tmp->value);
					i++;
				}
				tmp = tmp->next;
			}
			tab[i] = NULL;
		}
	}
	else
		tab[0] = NULL;
	return (tab);
}