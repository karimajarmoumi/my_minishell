/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:39:16 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 19:31:25 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

t_red	*init_red(int flg, int *i)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = NULL;
	red->flag = flg;
	if (flg == 2 || flg == 0)
		(*i) += 2;
	if (flg == 1 || flg == 3)
		(*i) += 1;
	return (red);
}

t_list	*init_lst(void)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	token->value = ft_strdup(value);
	token->e_type = type;
	return (token);
}
