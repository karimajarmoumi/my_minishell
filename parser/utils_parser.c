/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:09:24 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/19 01:11:45 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"


void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token 	*last_node;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last_node = ft_lstlast_token(*lst);
			last_node->next = new;
		}
	}
}

t_token 	*copy_of_list(t_token *original, int size)
{
	int		i;
	t_token 	*copy;

	i = 0;
	copy = NULL;
	if (original)
	{
		while (original && i < size)
		{
			ft_lstadd_back_token(&copy, init_token(original->value,
					original->type));
			original = original->next;
			i++;
		}
	}
	return (copy);
}

int	number_of_tokens_before_pipe(t_token *token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token && token->value[0] != '|')
		{
			i++;
			token = token->next;
		}
	}
	return (i);
}

t_token 	*tokens_of_one_command(t_token **token)
{
	int		i;
	int		count_token;
	t_token 	*tokens_cmd;

	i = 0;
	tokens_cmd = NULL;
	if (token && *token)
	{
		count_token = number_of_tokens_before_pipe(*token);
		tokens_cmd = copy_of_list(*token, count_token);
		while (*token && i <= count_token)
		{
			*token = (*token)->next;
			i++;
		}
	}
	return (tokens_cmd);
}

char	*tokens_cmd_to_string(t_token *token)
{
	char *buffer;

	buffer = ft_strdup("");
	if (token)
	{
		while (token)
		{
			buffer = ft_strjoin(buffer, token->value);
			token = token->next;
		}
		buffer = ft_strjoin(buffer, "\0");
	}
	return (buffer);
}