/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 01:09:19 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 18:05:34 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

int	ft_free_test(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = 0;
	}
	return (1);
}

void	function_free_token(void **to_free)
{
	t_token	*next;

	next = ((t_token *)(*to_free))->next;
	ft_free_test((void **)&((t_token *)(*to_free))->value);
	ft_free_test((void **)(to_free));
	*to_free = next;
}

int	function_free(void **to_free, int type)
{
	int		i;

	if (!type)
		(ft_free_test((void **)&(((t_lexer *)(*to_free))->content)))
	&& (ft_free_test(to_free));
	if (type == 1)
		ft_free_test(to_free);
	if (type == 2)
	{
		while (*to_free)
			function_free_token(to_free);
	}
	if (type == 3)
	{
		i = 0;
		while (to_free[i])
		{
			ft_free_test((void **)&(to_free[i]));
			i++;
		}
		ft_free_test((void **)to_free);
	}
	return (1);
}

void	free_same_type(void **f1, void **f2, int type)
{
	function_free(f1, type);
	function_free(f2, type);
}
