/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:24:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/18 18:20:09 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"


// int	count_cmds(t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token)
// 	{
// 		if (token->value[0] == '|')
// 			i++;
// 		token = token->next;
// 	}
// 	return (i);
// }

// t_list	*init_list(t_command *cmd)
// {
// 	t_list	*list;

// 	list = malloc(sizeof(t_list));
// 	list->content = (t_command *)cmd;
// 	list->next = NULL;
// 	return (list);
// }
