/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:37:52 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 20:07:59 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

char	*char_to_string(char c)
{
	char	*str;

	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*get_one_token(t_lexer *lexer, char *types)
{
	char		*buffer;
	t_token		*token;

	buffer = ft_strdup("");
	if (lexer->c == '>')
		return (token = init_token(">", red_output),
			lexer_advance(lexer), ft_free_test((void **)&buffer), token);
	if (lexer->c == '<')
		return (token = init_token("<", red_input),
			lexer_advance(lexer), ft_free_test((void **)&buffer), token);
	if (lexer->c == '|')
		return (token = init_token("|", token_pipe),
			lexer_advance(lexer), ft_free_test((void **)&buffer), token);
	if (lexer->c == ' ')
		return (token = init_token(" ", token_space),
			lexer_advance(lexer), ft_free_test((void **)&buffer), token);
	if (lexer->c == '\"' || lexer->c == '\'')
		return (get_one_token_with_quote(lexer));
	if (lexer->c == '$')
		return (get_one_token_with_dollar(lexer));
	return (get_one_token_text(lexer, types));
}

t_token	*get_all_tokens(t_lexer *lexer)
{
	char	*types;
	t_token	*head;
	t_token	*token;

	head = NULL;
	types = ft_strdup("<>| '\"");
	while (lexer->c != '\0')
	{
		token = get_one_token(lexer, types);
		if (token != NULL)
			ft_lstadd_back_token(&head, token);
	}
	ft_lstadd_back_token(&head, NULL);
	function_free((void **)&types, 1);
	return (head);
}
