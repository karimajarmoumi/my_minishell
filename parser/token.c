/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:37:52 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/21 02:17:22 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	return (token);
}

char *char_to_string(char c)
{
	char *str;

	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token *get_one_token(t_lexer *lexer, char *types)
{
	char		qoute;
	t_token		*token;
	char		*c_string;
	char		*buffer;
	char		*to_free;
	t_token		*ret;

	buffer = ft_strdup("");
	if (lexer->c == '>')
		return (token = init_token(">", red_output) ,lexer_advance(lexer), ft_free_test((void**)&buffer), token);
	if (lexer->c == '<')
		return (token = init_token("<", red_input) ,lexer_advance(lexer), ft_free_test((void**)&buffer), token);
	if (lexer->c == '|')
		return (token = init_token("|", token_pipe), lexer_advance(lexer), ft_free_test((void**)&buffer), token);
	if (lexer->c == ' ')
		return (token = init_token(" ", token_space), lexer_advance(lexer), ft_free_test((void**)&buffer),token);
	if (lexer->c == '\"' || lexer->c == '\'')
	{
		qoute = lexer->c;
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		function_free((void**)&c_string, 1);
		function_free((void**)&to_free, 1);
		lexer_advance(lexer);
		while (lexer->c != '\0' && lexer->c != qoute)
		{
			to_free = buffer;
			c_string = char_to_string(lexer->c);
			buffer = ft_strjoin(buffer, c_string);
			function_free((void**)&c_string, 1);
			function_free((void**)&to_free, 1);
			lexer_advance(lexer);
		}
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		function_free((void**)&c_string, 1);
		function_free((void**)&to_free, 1);
		lexer_advance(lexer);
		return (ret = init_token(buffer, token_s_qoute), ft_free_test((void**)&buffer), ret);
	}
	if (lexer->c == '$')
	{
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		function_free((void**)&c_string, 1);
		function_free((void**)&to_free, 1);
		lexer_advance(lexer);
		while (!ft_strchr(" '\"\0", lexer->c))
		{
			to_free = buffer;
			c_string = char_to_string(lexer->c);
			buffer = ft_strjoin(buffer, c_string);
			function_free((void**)&c_string, 1);
			function_free((void**)&to_free, 1);
			lexer_advance(lexer);
		}
		return (ret = init_token(buffer, token_dollar),
			 ft_free_test((void**)&buffer), ret);
	}
	while (!ft_strchr(types, lexer->c))
	{
		to_free = buffer;
		c_string = char_to_string(lexer->c);
		buffer = ft_strjoin(buffer, c_string);
		function_free((void**)&to_free, 1);
		function_free((void**)&c_string, 1);
		lexer_advance(lexer);
	}
	return (ret = init_token(buffer, token_text), ft_free_test((void**)&buffer), ret);
}


t_token *get_all_tokens(t_lexer *lexer, char *types)
{
	t_token	*head;
	t_token	*token;

	head = NULL;
	while (lexer->c != '\0')
	{
		token = get_one_token(lexer, types);

		if (token != NULL)
			ft_lstadd_back_token(&head, token);
	}
	ft_lstadd_back_token(&head, NULL);
	return (head);
}