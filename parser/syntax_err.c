/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:28:31 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 06:01:10 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

int	pipe_error_part1(t_token *tokens)
{
	char	*buffer;
	char	*to_free;

	buffer = ft_strdup("syntax error near unexpected token `|");
	if (tokens && tokens->value[0] == '|')
	{
		to_free = buffer;
		buffer = ft_strjoin(buffer, "|");
		function_free((void **)&to_free, 1);
		tokens = tokens->next;
	}
	to_free = buffer;
	buffer = ft_strjoin(buffer, "'");
	print_cmd_error(NULL, NULL, buffer, 258);
	free_same_type((void **)&to_free, (void **)&buffer, 1);
	return (1);
}

int	pipe_error(t_token *tokens, t_token *prev)
{
	if (tokens)
	{
		tokens = tokens->next;
		if (!prev)
			return (pipe_error_part1(tokens));
		else
		{
			while (tokens && tokens->e_type == 4)
				tokens = tokens->next;
			if (!tokens || (tokens && tokens->e_type == 2))
			{
				print_cmd_error(NULL, NULL,
					"syntax error near unexpected token `|'", 258);
				return (1);
			}
		}
	}
	return (0);
}

int	qoute_error(t_token *token)
{
	if (token)
	{
		if (ft_strlen(token->value) == 1)
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
		else if (token->value[ft_strlen(token->value) - 1] != token->value[0])
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
	}
	return (0);
}

int	redir_error(t_token *token, int type)
{
	if (token)
	{
		if (type == 0 && redir_in_error(token))
			return (1);
		else if (type == 1 && redir_out_error(token))
			return (1);
	}
	return (0);
}

void	check_parsing_error(t_token *tokens, int *flg_err)
{
	t_token	*prev;

	prev = NULL;
	if (tokens)
	{
		while (tokens)
		{
			if (tokens->e_type == 3)
				prev = tokens;
			(tokens->value[0] == '|') && (*flg_err = pipe_error(tokens, prev));
			if (*flg_err)
				break ;
			(tokens->value[0] == '<') && (*flg_err = redir_error(tokens, 0));
			if (*flg_err)
				break ;
			(tokens->value[0] == '>') && (*flg_err = redir_error(tokens, 1));
			if (*flg_err)
				break ;
			(tokens->e_type == 5 || tokens->e_type == 6)
				&& (*flg_err = qoute_error(tokens));
			if (*flg_err)
				break ;
			tokens = tokens->next;
		}
	}
}
