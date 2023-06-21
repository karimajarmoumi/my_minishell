/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:39:02 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/19 01:08:19 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lexer.h"

typedef struct s_token
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
	struct s_token	*next;
}					t_token;

t_token 				*init_token(char *value, int type);
t_token 				*get_one_token(t_lexer *lexer, char *types);
t_token 				*get_all_tokens(t_lexer *lexer, char *types);
t_token 				*tokens(t_token **token);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
t_token 				*ft_lstlast_token(t_token *lst);
char				*char_to_string(char c);

#endif