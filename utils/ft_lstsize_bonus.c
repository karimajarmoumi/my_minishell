/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:23:33 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/15 18:37:32 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
int	ft_lstsize_token(token_t *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		if(strcmp(lst->value," "))
			len++;
		lst = lst->next;
	}
	return (len);
}
