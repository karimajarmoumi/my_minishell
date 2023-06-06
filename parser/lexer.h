/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:33:06 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/22 17:32:18 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>


typedef struct lexer_s
{
	char	c;
	size_t	i;
	char	*content;
} lexer_t;

lexer_t		*init_lexer(char *content);
int			lexer_advance(lexer_t *lexer);
int			lexer_skip_whitespace(lexer_t *lexer);

#endif