/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:05:59 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/22 23:45:52 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "cmd.h"
#include "lexer.h"
#include "tree.h"
#include "../minishell.h"



token_t *tokens(token_t **token)
{
	token_t *cpy;
	token_t *tmp;
	token_t *lst_node;

	tmp = NULL;
	cpy = NULL;
	if (token && *token)
	{
		while ((*token && (*token)->value[0] != '|'))
		{
			//tmp
			(*token) = (*token)->next;
		}
		if (*token)
		{
			lst_node = ft_lstlast_token(tmp);
			lst_node->next = NULL;
		}
	}
	return (tmp);
}