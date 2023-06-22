/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:06:28 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 22:57:18 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	store_data_before_dollar(char **token, char **store)
{
	int	pos_dollar;

	pos_dollar = searching_for_char(*token, '$');
	if (pos_dollar != -1)
	{
		*store = ft_substr(*token, 0, pos_dollar);
		*token = ft_substr(*token, pos_dollar, ft_strlen(*token)
				- pos_dollar);
	}
}

void	check_dollar(char *token, char **store, int *i, int *flag)
{
	if (!ft_strcmp(token, "$") || (token[*i] == '$'
			&& !ft_isalnum(token[(*i) + 1]) && token[(*i) + 1] != '?'))
		*store = ft_strjoin(*store, "$");
	if (token[*i] == '$')
	{
		(*i)++;
		*flag = 0;
	}
	else
		*flag = 1;
}

void	string_to_expand(char *token, int *i, char **result)
{
	char	*c_string;

	while (token[*i] && (ft_isalnum(token[*i])
			|| token[*i] == '_' || token[*i] == '?'))
	{
		c_string = char_to_string(token[*i]);
		*result = ft_strjoin(*result, c_string);
		(*i)++;
	}
}

void	expand_result(char *result, int *flag, char **store)
{
	char	*value;

	if (!*flag)
		value = get_env(result);
	else
		value = ft_strdup(result);
	if (value)
		*store = ft_strjoin(*store, value);
	else
		*store = ft_strjoin(*store, ft_strdup(""));
	*flag = 0;
}

void	store_special_char(char *token, int *i, char **result, char **store)
{
	char	*c_string;

	while (token[*i] && !ft_isalnum(token[*i])
		&& token[*i] != '_' && token[*i] != '$')
	{
		c_string = char_to_string(token[*i]);
		*result = ft_strjoin(*result, c_string);
		(*i)++;
	}
	*store = ft_strjoin(*store, *result);
}
