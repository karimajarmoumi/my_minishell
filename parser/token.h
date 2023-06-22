/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:39:02 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 20:09:04 by kjarmoum         ###   ########.fr       */
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
		red_input,
		red_output,
		token_pipe,
		token_text,
		token_space,
		token_s_qoute,
		token_d_qoute,
		token_dollar
	} e_type;
	struct s_token	*next;
}					t_token;

char		*char_to_string(char c);
void		ft_lstadd_back_token(t_token **lst, t_token *new);
t_token		*init_token(char *value, int type);
t_token		*get_one_token(t_lexer *lexer, char *types);
t_token		*get_all_tokens(t_lexer *lexer);
t_token		*tokens(t_token **token);
t_token		*ft_lstlast_token(t_token *lst);

#endif