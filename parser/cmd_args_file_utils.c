/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_file_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:42:10 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 19:57:50 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	cmd_args_file_redir_part1(t_token **token_cmd, t_token **symb_fl)
{
	t_token		*prev;

	ft_lstadd_back_token(symb_fl, init_token((*token_cmd)->value,
			(*token_cmd)->e_type));
	prev = (*token_cmd);
	(*token_cmd) = (*token_cmd)->next;
	if ((*token_cmd) && (*token_cmd)->e_type == prev->e_type)
	{
		ft_lstadd_back_token(symb_fl, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
		(*token_cmd) = (*token_cmd)->next;
	}
	while ((*token_cmd) && (*token_cmd)->e_type == 4)
	{
		ft_lstadd_back_token(symb_fl, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
		(*token_cmd) = (*token_cmd)->next;
	}
}

void	cmd_args_file_redir_part2(t_token **token_cmd,
	t_token **symb_fl, int *flag)
{
	char		*prev_str;

	while ((*token_cmd) && ((*token_cmd)->e_type == 3
			|| (*token_cmd)->e_type == 7))
	{
		check_tild(&(*token_cmd));
		prev_str = ft_strdup((*token_cmd)->value);
		expand(&(*token_cmd)->value);
		expand_with_quote((*token_cmd));
		if ((*token_cmd)->value[0] == '\0')
			(*token_cmd)->value = ft_strdup(prev_str);
		function_free((void **)&prev_str, 1);
		ft_lstadd_back_token(symb_fl, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
		(*token_cmd) = (*token_cmd)->next;
	}
	*flag = 0;
}

void	cmd_args_file_store_spaces(t_token **token_cmd, t_token **cmd_arg)
{
	while ((*token_cmd) && (*token_cmd)->e_type == 4)
	{
		remove_s_d_qoute(&(*token_cmd)->value);
		ft_lstadd_back_token(cmd_arg, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
		(*token_cmd) = (*token_cmd)->next;
	}
}

void	cmd_args_file_store_text(t_token **token_cmd, int *flag)
{
	char		*to_free;
	char		*result;
	t_token		*tmp;
	t_token		*prev;

	tmp = *token_cmd;
	result = ft_strdup("");
	while (tmp && (tmp->e_type == 3 || tmp->e_type == 5 || tmp->e_type == 6))
	{
		to_free = result;
		result = ft_strjoin(result, expand_with_quote(tmp));
		function_free((void **)&to_free, 1);
		prev = tmp;
		tmp = tmp->next;
	}
	(*token_cmd) = prev;
	function_free((void **)&(*token_cmd)->value, 1);
	(*token_cmd)->value = ft_strdup(result);
	function_free((void **)&result, 1);
	check_tild(&(*token_cmd));
	expand(&(*token_cmd)->value);
	remove_s_d_qoute(&(*token_cmd)->value);
	*flag = 1;
}
