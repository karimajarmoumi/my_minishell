/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:33:18 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 17:55:07 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	cmd_args_file_store_quoted_text(t_token **token_cmd)
{
	t_token		*tmp;
	t_token		*prev;
	char		*to_free;
	char		*result;

	tmp = (*token_cmd);
	result = ft_strdup("");
	while (tmp && (tmp->e_type == 5 || tmp->e_type == 6))
	{
		to_free = result;
		result = ft_strjoin(result, expand_with_quote(tmp));
		function_free((void **)&to_free, 1);
		prev = tmp;
		tmp = tmp->next;
	}
	function_free((void **)&(*token_cmd)->value, 1);
	(*token_cmd) = prev;
	(*token_cmd)->value = result;
}

void	cmd_args_file_last(t_token **token_cmd,
		t_token **cmd_arg, t_token **symb_fl, int *flag)
{
	if ((*token_cmd) && ((*token_cmd)->e_type == 5
			|| (*token_cmd)->e_type == 6))
		cmd_args_file_store_quoted_text(&(*token_cmd));
	else
		expand(&(*token_cmd)->value);
	if ((*flag) == 0)
		ft_lstadd_back_token(symb_fl, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
	else if ((*flag) == 1 || (*flag) == -1)
		ft_lstadd_back_token(cmd_arg, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
	(*token_cmd) = (*token_cmd)->next;
}

void	cmd_args_file_body(t_token **token_cmd, t_token **cmd_arg,
		t_token **symb_fl, int *flag)
{
	if ((*token_cmd)->e_type == 0 || (*token_cmd)->e_type == 1)
	{
		cmd_args_file_redir_part1(&(*token_cmd), symb_fl);
		cmd_args_file_redir_part2(&(*token_cmd), symb_fl, flag);
	}
	else if ((*token_cmd) && (*token_cmd)->e_type == 4)
		cmd_args_file_store_spaces(&(*token_cmd), cmd_arg);
	else if ((*token_cmd) && (*token_cmd)->e_type == 3)
	{
		cmd_args_file_store_text(&(*token_cmd), flag);
		ft_lstadd_back_token(cmd_arg, init_token((*token_cmd)->value,
				(*token_cmd)->e_type));
		(*token_cmd) = (*token_cmd)->next;
	}
	else if ((*token_cmd))
		cmd_args_file_last(&(*token_cmd), cmd_arg, symb_fl, flag);
}

t_token	*cmd_args_file(t_token *token_cmd, char **symb_file)
{
	int			flag;
	t_token		*cmd_arg;
	t_token		*symb_fl;

	flag = -1;
	cmd_arg = NULL;
	symb_fl = NULL;
	if (token_cmd)
	{
		while (token_cmd)
		{
			cmd_args_file_body(&token_cmd, &cmd_arg, &symb_fl, &flag);
		}
		*symb_file = tokens_cmd_to_string(symb_fl);
		function_free((void **)&symb_fl, 2);
	}
	return (cmd_arg);
}
