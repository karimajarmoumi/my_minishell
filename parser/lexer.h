/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:33:06 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/18 22:26:09 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_lexer
{
	char	c;
	size_t	i;
	char	*content;
} t_lexer;

t_lexer		*init_lexer(char *content);
int			lexer_advance(t_lexer *lexer);
int			lexer_skip_whitespace(t_lexer *lexer);

#endif