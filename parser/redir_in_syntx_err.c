/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_syntx_err.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:40:10 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 06:03:17 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	redir_in_err_part1(t_token **token, int *flag)
{
	(*token) = (*token)->next;
	if ((*token) && ((*token)->e_type == 0))
	{
		(*token) = (*token)->next;
		*flag = 0;
	}
	if ((*token) && ((*token)->e_type == 0))
		(*token) = (*token)->next;
	while ((*token) && (*token)->e_type == 4)
		(*token) = (*token)->next;
}

int	redir_in_err_part2(t_token **token)
{
	int		i;
	char	*buffer;
	char	*to_free;

	i = 0;
	buffer = ft_strdup("syntax error near unexpected token `");
	while ((*token) && (((*token)->e_type == 0 && i < 3)
			|| ((*token)->e_type == 1 && i < 2)))
	{
		to_free = buffer;
		buffer = ft_strjoin(buffer, (*token)->value);
		function_free((void **)&to_free, 1);
		(*token) = (*token)->next;
		i++;
	}
	if ((*token) && (*token)->e_type == 2)
	{
		to_free = buffer;
		buffer = ft_strjoin(buffer, (*token)->value);
		function_free((void **)&to_free, 1);
	}
	print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
	return (1);
}

int	redir_in_error(t_token *token)
{
	int		i;
	int		flag;

	i = 0;
	flag = -1;
	if (token)
	{
		redir_in_err_part1(&token, &flag);
		if (!token || (token && flag && token->e_type == 1))
		{
			print_cmd_error(NULL, NULL,
				"syntax error near unexpected token `newline'", 258);
			return (1);
		}
		else if (token->e_type == 0 || token->e_type == 1 || token->e_type == 2)
		{
			return (redir_in_err_part2(&token));
		}
	}
	return (0);
}
