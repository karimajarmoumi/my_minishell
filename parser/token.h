/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:39:02 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/03 18:30:37 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lexer.h"

typedef struct token_s
{
	char			*value;
	enum
	{
		red_input,     // 0
		red_output,    // 1
		token_pipe,    // 2
		token_text,    // 3
		token_space,   // 4
		token_s_qoute, // 5
		token_d_qoute, // 6
		token_dollar   // 7
	} type;
	struct token_s	*next;
}					token_t;

token_t				*init_token(char *value, int type);
token_t				*get_one_token(lexer_t *lexer, char *types);
token_t				*get_all_tokens(lexer_t *lexer, char *types);
token_t				*tokens(token_t **token);
void				ft_lstadd_back_token(token_t **lst, token_t *new);
token_t				*ft_lstlast_token(token_t *lst);
char				*char_to_string(char c);

#endif