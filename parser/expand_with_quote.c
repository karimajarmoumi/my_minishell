/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_with_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 02:36:24 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 18:32:08 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

char	*expand_with_quote_d(t_token **token, int is_s_d_qoute)
{
	char	*before_dollar;
	char	*to_expand;
	char	*tmp;
	int		i;

	i = 0;
	remove_s_d_qoute(&(*token)->value);
	if (is_s_d_qoute == 2)
	{
		tmp = (*token)->value;
		while (tmp[i] && tmp[i] != '$')
			i++;
		before_dollar = ft_substr((*token)->value, 0, i);
		to_expand = ft_substr((*token)->value,
				get_char_position((*token)->value, '$'),
				ft_strlen((*token)->value) - i);
		expand(&to_expand);
		before_dollar = ft_strjoin(before_dollar, to_expand);
		return (before_dollar);
	}
	else
		return ((*token)->value);
}

char	*expand_with_quote(t_token *token)
{
	int		i;
	int		is_s_d_qoute;

	i = 0;
	is_s_d_qoute = -1;
	if (token && ft_strchr(token->value, '$'))
	{
		if (token->value[0] == '"')
			is_s_d_qoute = 2;
		else if (token->value[0] == '\'')
			is_s_d_qoute = 1;
		if (is_s_d_qoute != -1)
		{
			remove_s_d_qoute(&token->value);
			if (is_s_d_qoute == 2)
				return (expand_with_quote_d(&token, is_s_d_qoute));
			else
				return (token->value);
		}
		else
			expand(&token->value);
	}
	else
		remove_s_d_qoute(&token->value);
	return (token->value);
}
