/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_syntx_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 06:00:36 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 20:13:24 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

int	redir_out_error_part2(t_token **token)
{
	int		i;
	char	*buffer;
	char	*to_free;

	i = 0;
	buffer = ft_strdup("syntax error near unexpected token `");
	while ((*token) && ((i < 2 && ((*token)->e_type == 2
					|| (*token)->e_type == 1))
			|| (i < 3 && (*token)->e_type == 0)))
	{
		to_free = buffer;
		buffer = ft_strjoin(buffer, (*token)->value);
		function_free((void **)&to_free, 1);
		(*token) = (*token)->next;
		i++;
	}
	to_free = buffer;
	buffer = ft_strjoin(buffer, "'");
	print_cmd_error(NULL, NULL, buffer, 258);
	free_same_type((void **)&to_free, (void **)&buffer, 1);
	return (1);
}

int	redir_out_error(t_token *token)
{
	if (token)
	{
		token = token->next;
		if (token && token->e_type == 2)
		{
			token = token->next;
			while (token && token->e_type == 4)
				token = token->next;
			if (!token)
				return (print_cmd_error(NULL, NULL, MSG_ERR, 258), 1);
			return (0);
		}
		if (token && token->e_type == 1)
			token = token->next;
		while (token && token->e_type == 4)
			token = token->next;
		if (token && (token->e_type == 0
				|| token->e_type == 1 || token->e_type == 2))
			return (redir_out_error_part2(&token));
		if (!token)
			return (print_cmd_error(NULL, NULL, MSG_ERR, 258), 1);
	}
	return (0);
}
