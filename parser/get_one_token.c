/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_one_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:16:53 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 04:17:25 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	join_char(char **buffer, t_lexer *lexer)
{
	char	*to_free;
	char	*c_string;

	to_free = (*buffer);
	c_string = char_to_string(lexer->c);
	(*buffer) = ft_strjoin((*buffer), c_string);
	free_same_type((void **)&c_string, (void **)&to_free, 1);
	lexer_advance(lexer);
}

t_token	*get_one_token_with_quote(t_lexer *lexer)
{
	char	qoute;
	char	*to_free;
	char	*c_string;
	char	*buffer;
	t_token	*ret;

	buffer = ft_strdup("");
	qoute = lexer->c;
	to_free = buffer;
	c_string = char_to_string(lexer->c);
	buffer = ft_strjoin(buffer, c_string);
	free_same_type((void **)&c_string, (void **)&to_free, 1);
	lexer_advance(lexer);
	while (lexer->c != '\0' && lexer->c != qoute)
		join_char(&buffer, lexer);
	to_free = buffer;
	c_string = char_to_string(lexer->c);
	buffer = ft_strjoin(buffer, c_string);
	free_same_type((void **)&c_string, (void **)&to_free, 1);
	lexer_advance(lexer);
	return (ret = init_token(buffer, token_s_qoute)
		, ft_free_test((void **)&buffer), ret);
}

t_token	*get_one_token_with_dollar(t_lexer *lexer)
{
	char	*to_free;
	char	*c_string;
	char	*buffer;
	t_token	*ret;

	buffer = ft_strdup("");
	to_free = buffer;
	c_string = char_to_string(lexer->c);
	buffer = ft_strjoin(buffer, c_string);
	free_same_type((void **)&c_string, (void **)&to_free, 1);
	lexer_advance(lexer);
	while (!ft_strchr(" '\"\0", lexer->c))
	{
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		free_same_type((void **)&c_string, (void **)&to_free, 1);
		lexer_advance(lexer);
	}
	return (ret = init_token(buffer, token_dollar),
		ft_free_test((void **)&buffer), ret);
}

t_token	*get_one_token_text(t_lexer *lexer, char *types)
{
	char		*to_free;
	char		*c_string;
	char		*buffer;
	t_token		*ret;

	buffer = ft_strdup("");
	while (!ft_strchr(types, lexer->c))
	{
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		free_same_type((void **)&c_string, (void **)&to_free, 1);
		lexer_advance(lexer);
	}
	return (ret = init_token(buffer, token_text),
		ft_free_test((void **)&buffer), ret);
}
