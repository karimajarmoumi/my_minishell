/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 01:09:19 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/21 15:47:33 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"



int	ft_free_test(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = 0;
		//printf("jj %p\n",*ptr);
	}
	return (1);
}
 // 39 ls > out
void function_free(void **to_free, int type)
{
	// t_token *lst_token;
	t_token *next;

	//lexer;
	if (!type)
		ft_free_test((void **)&(((t_lexer *)(*to_free))->content)) && ft_free_test(to_free);
	//tab
	if (type == 1)
		ft_free_test(to_free);
	//token
	if (type == 2)
	{
		while (*to_free)
		{
			next = ((t_token *)(*to_free))->next;
			ft_free_test((void **)&((t_token *)(*to_free))->value);
			ft_free_test((void **)(to_free));
			*to_free = next;
		}
	}
	// char**
	int		i;
	if (type == 3)
	{
		i = 0;
		while (to_free[i])
		{
			ft_free_test((void **)&(to_free[i]));
			i++;
		}
		ft_free_test((void **)to_free);
		// printf("%p\n",to_free);

	}

}
