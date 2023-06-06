/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:33:16 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/21 17:41:50 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

lexer_t *init_lexer(char *content)
{
	lexer_t *lexer;
	lexer = calloc(1, sizeof(lexer_t));
	lexer->i = 0;
	lexer->content = malloc(sizeof(ft_strlen(content)));
	lexer->content = content;
	lexer->c = lexer->content[lexer->i];
	return (lexer);
}

int lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
	return (1);
}

int lexer_skip_whitespace(lexer_t *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
		lexer_advance(lexer);
	return (1);
}


