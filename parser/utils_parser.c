/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:09:24 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/14 17:25:52 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include "cmd.h"
#include "../minishell.h"

token_t	*ft_lstlast_token(token_t *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_token(token_t **lst, token_t *new)
{
	token_t	*last_node;

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

token_t *copy_of_list(token_t *original, int size)
{
	int		i;
	token_t *copy;

	i = 0;
	copy = NULL;
	if (original)
	{
		while (original && i < size)
		{
			ft_lstadd_back_token(&copy, init_token(original->value, original->type));
			original = original->next;
			i++;
		}
	}
	return (copy);
}

int	number_of_tokens_before_pipe(token_t *token)
{
	int i;

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

token_t *tokens_of_one_command(token_t **token)
{
	int		i;
	int		count_token;
	token_t *tokens_cmd;

	i = 0;
	tokens_cmd = NULL;

	if (token && *token)
	{
		count_token = number_of_tokens_before_pipe(*token);
		tokens_cmd = copy_of_list(*token ,count_token);
		while (*token  && i <= count_token)
		{
			*token = (*token)->next;
			i++;
		}
	}
	return (tokens_cmd);
}

char	*tokens_cmd_to_string(token_t *token)
{
	char	*buffer;

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