/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:28:31 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/21 03:12:10 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

int pipe_error(t_token *tokens, t_token *prev)
{
	char	*buffer;
	char	*to_free;

	if (tokens)
	{
		tokens = tokens->next;
		if (!prev)
		{
			buffer =  ft_strdup("syntax error near unexpected token `|");
			if (tokens && tokens->value[0] == '|')
			{
				to_free =buffer;
				buffer = ft_strjoin(buffer, "|");
				function_free((void**)&to_free, 1);
				tokens = tokens->next;
			}
			to_free =buffer;
			buffer = ft_strjoin(buffer, "'");
			function_free((void**)&to_free, 1);
			print_cmd_error(NULL, NULL, buffer, 258);
			function_free((void**)&buffer, 1);
			return (1);
		}
		else
		{
			while (tokens && tokens->type == 4)
				tokens = tokens->next;
			if (!tokens || (tokens && tokens->type == 2))
			{
				print_cmd_error(NULL, NULL, "syntax error near unexpected token `|'", 258);
				return (1);
			}
		}
	}
	return (0);
}

int qoute_error(t_token *token)
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

int redir_in_error(t_token *token)
{
	int		i;
	int		flag;
	char	*buffer;
	char	*to_free;

	i = 0;
	flag = -1;
	if (token)
	{
		token = token->next;
		if (token && (token->type == 0))
		{
			token = token->next;
			flag = 0;
		}
		if (token && (token->type == 0))
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (!token || (token && flag && token->type == 1))
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
		else if (token->type == 0 || token->type == 1 || token->type == 2)
		{
			buffer = ft_strdup("syntax error near unexpected token `");
			while (token && ((token->type == 0 && i < 3) || (token->type == 1 && i < 2)))
			{
				to_free = buffer;
				buffer = ft_strjoin(buffer, token->value);
				function_free((void**)&to_free, 1);
				token = token->next;
				i++;
			}

			//////while(1);
			if (token && token->type == 2)
			{
				to_free = buffer;
				buffer = ft_strjoin(buffer, token->value);
				function_free((void**)&to_free, 1);
			}
			print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
			return (1);
		}
	}
	return (0);
}

int redir_out_error(t_token *token)
{
	int		i;
	char	*buffer;
	char	*to_free;

	i = 0;
	if (token)
	{
		token = token->next;
		if (token && token->type == 2)
		{
			token = token->next;
			while (token && token->type == 4)
				token = token->next;
			if (!token)
			{
				print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
				return (1);
			}
			return (0);
		}
		if (token && token->type == 1)
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (token && (token->type == 0 || token->type == 1 || token->type == 2))
		{
			buffer = ft_strdup("syntax error near unexpected token `");
			while (token && ((i < 2 && (token->type == 2 || token->type == 1))
				|| (i < 3 && token->type == 0)))
			{
				to_free = buffer;
				buffer = ft_strjoin(buffer, token->value);
				function_free((void**)&to_free, 1);
				token = token->next;
				i++;
			}
			to_free = buffer;
			buffer=ft_strjoin(buffer, "'");
			print_cmd_error(NULL, NULL, buffer, 258);
			function_free((void**)&to_free, 1);
			function_free((void**)&buffer, 1);
			return (1);
		}
		if (!token)
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
	}
	return (0);
}

int redir_error(t_token *token, int type)
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

void check_parsing_error(t_token *tokens, int *flg_err)
{
	t_token *prev;

	prev = NULL;
	if (tokens)
	{
		while (tokens )
		{
			if (tokens->type == 3)
				prev = tokens;
			else if (tokens->value[0] == '|')
			{
				*flg_err = pipe_error(tokens, prev);
				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '<')
			{
				*flg_err = redir_error(tokens , 0);

				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '>')
			{
				*flg_err = redir_error(tokens , 1);
				if (*flg_err)
					break;
			}
			else
			 if (tokens->type == 5 || tokens->type == 6)
			{
				*flg_err = qoute_error(tokens);
				if (*flg_err)
					break;
			}

			tokens = tokens->next;
		}

	}
}
